/*------------------------------------------------------------
File: uart.c
Purpose: UART communication driver functions
------------------------------------------------------------*/

#include<LPC21xx.h>      // LPC21xx register definitions
#include"defines.h"      // Macro definitions
#include"pin_connect.h"  // Pin configuration functions
#include"types.h"        // User defined data types

//------------------------------------------------------------
//Function: InitUART
//Purpose : Initialize UART1 peripheral
//------------------------------------------------------------
void InitUART(void)
{
	      //PINSEL0|=0x00000001;
        CfgPinFunc(0,8,1);   // Configure P0.8 as TXD1
        CfgPinFunc(0,9,1);   // Configure P0.9 as RXD1

        U1LCR=0x03;          // 8-bit data, 1 stop bit
        U1LCR|=1<<7;         // Enable DLAB(DLAB=1)

        U1DLL=97;            // Set baud rate (low byte)
        U1DLM=0;             // Set baud rate (high byte)

        U1LCR&=~(1<<7);      // Disable DLAB(DLAB=0)
}

//------------------------------------------------------------
//Function: UARTRxChar
//Purpose : Receive one character from UART
//------------------------------------------------------------
s8 UARTRxChar(void)
{
	      while(!READBIT(U1LSR,0));   // Wait until data ready
        return (U1RBR);             // Return received byte
}

//------------------------------------------------------------
//Function: UARTTxChar
//Purpose : Transmit one character via UART
//------------------------------------------------------------
void UARTTxChar(s8 ch)
{
	      U1THR=ch;                   // Load data to transmit register
        while(!READBIT(U1LSR,6));   // Wait until transmission complete
}

//------------------------------------------------------------
//Function: UARTTxStr
//Purpose : Transmit string via UART
//------------------------------------------------------------
void UARTTxStr(s8 *ptr)
{
        while(*ptr)                 // Until null character
                UARTTxChar(*ptr++);
}

//------------------------------------------------------------
//Function: UARTTxU32
//Purpose : Transmit unsigned 32-bit number
//------------------------------------------------------------
void UARTTxU32(u32 num)
{
        u8 a[10];
        s8 i=0;
        //itoa
        if(num==0)
                UARTTxChar('0');
        else
        {
                while(num>0)              // Convert to ASCII
                {
                        a[i++]=num%10+48;
                        num=num/10;
                }
                for(--i;i>=0;i--)         // Print digits
                        UARTTxChar(a[i]);
        }
}

//------------------------------------------------------------
//Function: UARTTxF32
//Purpose : Transmit floating point number
//------------------------------------------------------------
void UARTTxF32(f32 fnum)
{
        u32 num,i;
        if(fnum<0)
        {
                UARTTxChar('-');
                fnum=-fnum;
        }
        num=fnum;                   // Integer part
        UARTTxU32(num);
        UARTTxChar('.');
        for(i=0;i<6;i++)            // 6 decimal places
        {
                fnum=(fnum-num)*10;
                num=fnum;
                UARTTxChar(num+48);
        }
}

//------------------------------------------------------------
//Function: UARTTx_SendRTC
//Purpose : Send RTC time and date via UART
//------------------------------------------------------------
void UARTTx_SendRTC(void)
{
    UARTTxChar((HOUR/10)+48); //Hour
    UARTTxChar((HOUR%10)+48);
    UARTTxChar(':');
    UARTTxChar((MIN/10)+48); //Minute
    UARTTxChar((MIN%10)+48);
    UARTTxChar(':');
    UARTTxChar((SEC/10)+48); //Second
    UARTTxChar((SEC%10)+48);
    UARTTxChar(' ');

    UARTTxChar((DOM/10)+48); //Date
    UARTTxChar((DOM%10)+48);
    UARTTxChar('/');
    UARTTxChar((MONTH/10)+48); //Month
    UARTTxChar((MONTH%10)+48);
    UARTTxChar('/');

    UARTTxChar((YEAR/1000)%10 + '0'); //Year
    UARTTxChar((YEAR/100)%10 + '0');
    UARTTxChar((YEAR/10)%10 + '0');
    UARTTxChar(YEAR%10 + '0');

    //UARTTxStr("\r\n");
}
