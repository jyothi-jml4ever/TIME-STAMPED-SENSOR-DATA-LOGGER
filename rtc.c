/*------------------------------------------------------------
File: rtc.c
Purpose: RTC driver functions for time, date and temperature display
------------------------------------------------------------*/
#include <LPC21xx.H> //Header with LPC21xx register definitions
#include "rtc_defines.h"    // RTC related macros
#include "types.h"          // User defined data types
#include "lcd.h"            // LCD interface functions
#include "lm35.h"           // LM35 temperature sensor functions

extern f32 Temp;            // Global temperature variable

// Array to hold names of days of the week
char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};
//extern char week[][4];

//------------------------------------------------------------
//Function: RTC_Init
//Purpose : Initialize the Real-Time Clock (RTC) 
//          This function disables the RTC, sets the prescaler values,
//          and then enables the RTC.
//------------------------------------------------------------
void RTC_Init(void)
{
  // Disable and reset the RTC
        CCR = RTC_RESET;

#ifdef _LPC2148
  // Enable the RTC & select the clock source
        CCR = RTC_ENABLE | RTC_CLKSRC;
#else
  // Set prescaler integer and fractional parts
        PREINT = PREINT_VAL;
        PREFRAC= PREFRAC_VAL;

  // Enable the RTC
        CCR = RTC_ENABLE;

#endif

}

//------------------------------------------------------------
//Function: GetRTCTimeInfo
//Purpose : Get the current RTC time
//------------------------------------------------------------
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
        *hour = HOUR; //hour Pointer to store the current hour
        *minute = MIN; //minute Pointer to store the current minute
        *second = SEC; //second Pointer to store the current second
}

//------------------------------------------------------------
//Function: DisplayRTCTime
//Purpose : Display the RTC time on LCD seperated by ':'
//------------------------------------------------------------
void DisplayRTCTime(u32 hour, u32 minute, u32 second)
{
                CmdLCD(0x80);
	              //hour value (0-23)
                CharLCD((hour/10)+48);
                CharLCD((hour%10)+48);
                CharLCD(':');
	              //minute value (0-59)
                CharLCD((minute/10)+48);
                CharLCD((minute%10)+48);
                CharLCD(':');
	              //second value (0-59)
                CharLCD((second/10)+48);
                CharLCD((second%10)+48);

}

//------------------------------------------------------------
//Function: GetRTCDateInfo
//Purpose : Get the current RTC date
//------------------------------------------------------------
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
        *date = DOM; //day Pointer to store the current date (1-31)
        *month = MONTH; //month Pointer to store the current month (1-12)
        *year = YEAR; //year Pointer to store the current year (four digits)
}

//------------------------------------------------------------
//Function: DisplayRTCDate
//Purpose : Display the RTC date on LCD and seperated by '/'
//------------------------------------------------------------
void DisplayRTCDate(u32 date, u32 month, u32 year)
{
                CmdLCD(0xC0);
	              //Day of month (1-31)
                CharLCD((date/10)+48);
                CharLCD((date%10)+48);
                CharLCD('/');
	              //Month (1-12)
                CharLCD((month/10)+48);
                CharLCD((month%10)+48);
                CharLCD('/');
	              //Year (four digits)
                IntLCD(year);
}

//------------------------------------------------------------
//Function: SetRTCTimeInfo
//Purpose : Set the RTC time
//------------------------------------------------------------
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
{
        HOUR = hour; //Hour to set (0-23)
        MIN = minute; //Minute to set (0-59)
        SEC = second; //Second to set (0-59)
}

//------------------------------------------------------------
//Function: SetRTCDateInfo
//Purpose : Set the RTC date
//------------------------------------------------------------
void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
        DOM = date; //day of month to set (1-31)
        MONTH = month; //month to set (1-12)
        YEAR = year; //year to set (four digits)
}

//------------------------------------------------------------
//Function: GetRTCDay
//Purpose : Get the current day of the week
//------------------------------------------------------------
void GetRTCDay(s32 *day)
{
        *day = DOW; //dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)
}

//------------------------------------------------------------
//Function: DisplayRTCDay
//Purpose : Display the current day of the week on LCD
//------------------------------------------------------------
void DisplayRTCDay(u32 dow)
{
        CmdLCD(0xCC);
        StrLCD(week[dow]); //dow (Day of Week) (0=Sunday, ..., 6=Saturday)
}

//------------------------------------------------------------
//Function: DisplayRTCDay
//Purpose : Set the day of the week in RTC
//------------------------------------------------------------
void SetRTCDay(u32 day)
{
        DOW = day; //Day of Week to set (0=Sunday, ..., 6=Saturday)
}

//------------------------------------------------------------
//Function: DisplayTemp
//Purpose : Display temperature on LCD
//------------------------------------------------------------
void DisplayTemp(void)
{
        CmdLCD(0x8B);
        IntLCD(Read_LM35('C'));
        CmdLCD(0x48);//Cursor is placed at CGRAM loc
        StoreCustCharFont();
        CmdLCD(0x8D);
        CharLCD(1);//font is read from 8*1+0x40 loc
        CmdLCD(0x8E);
        CharLCD('C');
}
