/*------------------------------------------------------------
File: main_fun.c
Purpose: Main application functions (RTC, LCD, UART, Keypad)
------------------------------------------------------------*/
#include "main.h"

/* RTC variables must be s32 (driver requirement) */
s32 hour, min, sec, date, month, year, day;
u32 SP = 40; // Set Point temperature

//------------------------------------------------------------
//Function: ALERT_Info_On_UART
//Purpose : Send alert message on UART for Every 1minute
//------------------------------------------------------------
void ALERT_Info_On_UART(void)
{
    static s32 last_sec = -1; // Store previous second

    if (sec != last_sec)
    {
        last_sec = sec;

        if (sec == 59) // Check last second
        {
            UARTTxStr("Temp: ");
            UARTTxF32(Read_LM35('C'));
            UARTTxStr(" C @");
            UARTTx_SendRTC();
            UARTTxStr(" -OVER TEMP!\r\n");
        }
    }
}

//------------------------------------------------------------
//Function: Info_On_LCD
//Purpose : Display RTC and temperature on LCD
//------------------------------------------------------------
void Info_On_LCD(void)
{
    GetRTCTimeInfo(&hour, &min, &sec);
    DisplayRTCTime(hour, min, sec);

    DisplayTemp();

    GetRTCDateInfo(&date, &month, &year);
    DisplayRTCDate(date, month, year);

    GetRTCDay(&day);
    DisplayRTCDay(day);
}

//------------------------------------------------------------
//Function: Info_On_UART
//Purpose : Send periodic RTC and temperature info on UART
//------------------------------------------------------------
void Info_On_UART(void)
{
    static s32 last_sec = -1;

    if (sec != last_sec)
    {
        last_sec = sec;

        if (sec == 59)
        {
            UARTTxStr("Temp: ");
            UARTTxF32(Read_LM35('C'));
            UARTTxStr(" C @");
            UARTTx_SendRTC();
            UARTTxStr("\r\n");
        }
    }
}

//------------------------------------------------------------
//Function: MAIN_MENU
//Purpose : Display main menu on LCD
//------------------------------------------------------------
void MAIN_MENU(void)
{
    CmdLCD(0x01); // Clear LCD
    StrLCD("1.EDIT RTC INFO");
    CmdLCD(0xC0);
    StrLCD("2.EDIT SP 3.EXIT");
}

//------------------------------------------------------------
//Function: RTC_MENU
//Purpose : Display RTC edit menu
//------------------------------------------------------------
void RTC_MENU(void)
{
    CmdLCD(0x01);
    StrLCD("1.H 2.M 3.S 4.D");
    CmdLCD(0xC0);
    StrLCD("5.M 6.Y 7.D 8.E");
}

//------------------------------------------------------------
//Function: EDIT_RTC_Info
//Purpose : Edit RTC parameters using keypad
//------------------------------------------------------------
void Edit_RTC_Info(void)
{
    s32 temp;
    u8 weekday;

    while (1)
    {
        u8 key;

        while (ColStat()); // Wait for key press
        delay_ms(10);
        key = KeyVal();
        while (!ColStat()); // Wait for key release

        CmdLCD(0x01);

        switch (key)
        {
            case 1: // Edit Hour
                StrLCD("Enter Hour:");
                temp = Num_from_KeyPd(2);
                HOUR = (temp > 23) ? 23 : temp;
                break;

            case 2: // Edit Minute
                StrLCD("Enter Minute:");
                temp = Num_from_KeyPd(2);
                MIN = (temp > 59) ? 59 : temp;
                break;

            case 3: // Edit Second
                StrLCD("Enter Second:");
                temp = Num_from_KeyPd(2);
                SEC = (temp > 59) ? 59 : temp;
                break;

            case 4: // Edit Date
                StrLCD("Enter Date:");
                temp = Num_from_KeyPd(2);
                DOM = (temp < 1 || temp > 31) ? 1 : temp;
                break;

            case 5: // Edit Month
                StrLCD("Enter Month:");
                temp = Num_from_KeyPd(2);
                MONTH = (temp < 1 || temp > 12) ? 1 : temp;
                break;

            case 6: // Edit Year
                StrLCD("Enter Year:");
                temp = Num_from_KeyPd(4);
                YEAR = (temp < 2000) ? 2000 : temp;
                break;

            case 7: // Update Day
                weekday = GetDayFromDate();
                SetRTCDay(weekday);
                CmdLCD(0x01);
                StrLCD("Day Updated");
                delay_ms(500);
                break;

            case 8: //Save & Exit
                SetRTCTimeInfo(HOUR, MIN, SEC);
                SetRTCDateInfo(DOM, MONTH, YEAR);
                CmdLCD(0x01);
                StrLCD("Saved");
                delay_ms(800);
                return;
        }

        RTC_MENU();
    }
}

//------------------------------------------------------------
//Function: Num_from_KeyPd
//Purpose : Read numeric input from keypad 
//------------------------------------------------------------
u32 Num_from_KeyPd(u8 max_digits)
{
    u32 num = 0;
    u8 key, digit_cnt = 0;

    CmdLCD(0xC0);

    while (1)
    {
        while (ColStat());
        delay_ms(10);
        key = KeyVal();
        while (!ColStat());

        if (key <= 9 && digit_cnt < max_digits)
        {
            num = (num * 10) + key;
            digit_cnt++;
            IntLCD(key);
        }
        else if (key == KP_BACKSPACE && digit_cnt > 0)
        {
            num /= 10;
            digit_cnt--;
            CmdLCD(0x10);
            CharLCD(' ');
            CmdLCD(0x10);
        }
        else if (key == KP_ENTER)
        {
            while (!ColStat());   // wait for release
            return num;
        }
    }
}

//------------------------------------------------------------
//Function: GetDayFromDate
//Purpose : Get weekday from user input
//------------------------------------------------------------
u8 GetDayFromDate(void)
{
    u8 key;

    CmdLCD(0x01);
    StrLCD("0-S 1-M 2-T 3-W");
    CmdLCD(0xC0);
    StrLCD("4-T 5-F 6-S");

    while (1)
    {
        while (ColStat());
        delay_ms(10);
        key = KeyVal();
        while (!ColStat());

        if (key <= 6)
            return key;
    }
}

//------------------------------------------------------------
//Function: EDIT_SP
//Purpose : Edit set point temperature
//------------------------------------------------------------
void EDIT_SP(void)
{
    CmdLCD(0x01);
    StrLCD("Enter SP:");

    SP = Num_from_KeyPd(3);
    if (SP > 150) SP = 150; // Limit SP

    CmdLCD(0x01);
    StrLCD("SP Saved");
    delay_ms(1000);
}
