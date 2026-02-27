/*------------------------------------------------------------
File: main.c
Purpose:     
    Controls:
        - Temperature monitoring using LM35
        - RTC date & time display
        - LCD & UART information display
        - Alert system (LED + Buzzer)
        - Edit mode (RTC & Set Point editing)
    System Modes:
        1. Normal Mode  -> Monitoring + Display
        2. Edit Mode    -> Modify Time or Set Point
------------------------------------------------------------*/
#include "main.h" //Header file for main application functions

extern u32 SP;    // Set Point temperature
//------------------------------------------------------------
//Function: main
//Purpose :
//    Entry point of program execution.
//Main Workflow:
//    1. Initialize hardware peripherals
//    2. Set default RTC values
//    3. Continuously monitor temperature
//    4. Trigger alert if temperature >= SP
//    5. Allow user to enter Edit Mode via switch
//------------------------------------------------------------
int main(void)
{
    u32 flag = 0;    // flag=0 -> Normal mode
                     // flag=1 -> Edit mode

	  /* Configure LED and BUZZER as output for alert*/
    IODIR1 |= (1 << LED) | (1 << BUZZER);
    IOCLR1  = (1 << LED);
	
    IOSET1  = (1 << BUZZER);

    /* Peripheral Initialization */
    RTC_Init();        // Initialize RTC
    InitLCD();         // Initialize LCD
    InitUART();        // Initialize UART
    Init_ADC(CH1);     // Initialize ADC channel
    KeyPdInit();       // Initialize keypad

	  /* Default RTC Settings */
	  SetRTCTimeInfo(12, 0, 0); //Hour:Minute:Second
    SetRTCDateInfo(1, 1, 2026); //Day-Month-Year
	  SetRTCDay(4); //(0=Sunday, ..., 6=Saturday)

    while (1)
    {
			  /* Normal condition (Always reset outputs before checking temperature) */
			  IOCLR1 = (1 << LED);
        IOSET1 = (1 << BUZZER);
			
			  /* ---------------------------------------------------
           Temperature Monitoring Logic
           ---------------------------------------------------
           Read LM35 temperature.
           If temperature >= Set Point:
               -> Turn ON LED
               -> Turn ON Buzzer
               -> Send alert message through UART
        ---------------------------------------------------*/
        if (Read_LM35('C') >= SP)
        {
            IOSET1 = (1 << LED);    //LED ON
            IOCLR1 = (1 << BUZZER); //Buzzer ON
            ALERT_Info_On_UART();   //Send alert
        }
			
			  /* ---------------------------------------------------
           Switch Press Detection
           ---------------------------------------------------
           If switch is pressed:
               -> Enter Edit Mode
               -> Show Main Menu
        ---------------------------------------------------*/
        if (((IOPIN1 >> SW) & 1) == 0)
        {
            delay_ms(10); // debounce delay
            while (((IOPIN1 >> SW) & 1) == 0); // wait until switch released

            flag = 1;    // enter edit mode
            MAIN_MENU(); // display menu

            while (flag)
            {
                u8 key;

                while (ColStat()); //Wait for keypad press
                delay_ms(10);
                key = KeyVal();
                while (!ColStat()); //Wait for keypad release 

							  // RTC Editing Mode
                if (key == 1)
                {
									  // RTC Editing Mode
                    UARTTxStr("*** Time Edit Mode ***\r\n");
                    RTC_MENU();
                    Edit_RTC_Info();
                    MAIN_MENU();
                }
                else if (key == 2)
                {
									  // Set Point Editing Mode
                    UARTTxStr("*** SP Edit Mode ***\r\n");
                    EDIT_SP();
                    MAIN_MENU();
                }
                else if (key == 3)
                {
									  // Exit Edit Mode
                    flag = 0;
                    UARTTxStr("*** Exit Edit Mode ***\r\n");
                    CmdLCD(0x01);
                }
            }
        }
				
        /* ---------------------------------------------------
           Normal Display Mode
           ---------------------------------------------------
           If not in edit mode:
               -> Continuously display
                 Time, Date, Temp on LCD
               -> Send info via UART for every 1minute
        ---------------------------------------------------*/
        if (flag == 0)
        {
            Info_On_LCD();
            Info_On_UART();
        }

    }
}
