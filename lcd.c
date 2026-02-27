/*------------------------------------------------------------
File: lcd.c
Purpose: LCD Driver Implementation for 16x2 Character LCD
         (HD44780)
------------------------------------------------------------*/
#include <LPC21xx.h> //Header with LPC21xx register definitions
#include "delay.h"   //Provides software delay function declarations
#include "lcd.h"     //LCD Driver Header File
#include "types.h"   //User-defined data type definitions (type aliasing)
#include "defines.h" //Provides commonly used bit manipulation macros

/* LCD Data and Control Pin Definitions */
#define LCD_DAT 0xff   // Data lines mask (P0.16–P0.23)
#define RS 10          // P0.13 -> Register Select
#define RW 11          // P0.14 -> Read/Write
#define EN 12          // P0.15 -> Enable

//------------------------------------------------------------
//Function: InitLCd
//Purpose : Initialize LCD in 8-bit mode.

//Initialization Sequence (as per HD44780 datasheet):
//    1. Wait >15ms after power ON
//    2. Send 0x30 three times (force 8-bit mode)
//    3. Configure function set
//    4. Clear display
//    5. Set entry mode
//    6. Turn display ON
//------------------------------------------------------------
void InitLCD(void)
{
	//P0.13-P0.23--By default GPIO pins
	IODIR0|=((LCD_DAT<<0)|(1<<RS)|(1<<RW)|(1<<EN));
	
	delay_ms(20);//min 15 msec required
	CmdLCD(0x30);//8-bit mode enabling
	delay_ms(10);//min. of 5 msec
	CmdLCD(0x30);//8-bit mode enabling
	delay_ms(1);//min. of 160 usec
	CmdLCD(0x30);//8-bit mode enabling
	delay_ms(1);//min. of 160 usec
	CmdLCD(0x38);//8-bit with 5*7 font 1 lines disp
	CmdLCD(0x10);//Display off
	CmdLCD(0x01);//Clear display
	CmdLCD(0x06);//Set cursor move direction
	CmdLCD(0x0f);//Disp ON ,cursor ON with Blinking
}

//------------------------------------------------------------
//Function: CmdLCD
//Purpose : Send command instruction to LCD.
//Working:
//    RS = 0 -> Command register selected
//    RW = 0 -> Write operation
//------------------------------------------------------------
void CmdLCD(u8 cmd)
{
	IOCLR0=1<<RS;//clear P0.13-->RS of LCD
	DispLCD(cmd);
}

//------------------------------------------------------------
//Function: CharLCD
//Purpose : Display single character on LCD.
//Working:
//    RS = 1 -> Data register selected
//    RW = 0 -> Write operation
//------------------------------------------------------------
void CharLCD(u8 dat)
{
	IOSET0=1<<RS;//SET P0.13-->RS of LCD
	DispLCD(dat);
}

//------------------------------------------------------------
//Function: DispLCD
//Purpose : Low-level function to send byte to LCD.
//Working Steps:
//    1. RW = 0 ? Write mode
//    2. Put data on P0.16–P0.23
//    3. EN = 1 ? Latch data
//    4. EN = 0 ? Complete write cycle
//------------------------------------------------------------
void DispLCD(u8 val)
{
	IOCLR0=1<<RW;//clear P0.14--->RW of LCD
	WRITEBYTE(IOPIN0,0,val);//write cmd to P0.16-P0.23
	IOSET0=1<<EN;//make (P0.15)En high
	delay_ms(2);//min. of 450 nsec expected
	IOCLR0=1<<EN;//clear P0.15--->EN of LCD
	delay_ms(5);
}

//------------------------------------------------------------
//Function: StrLCD
//Purpose : Display null-terminated string on LCD.
//Logic: Keep printing characters until '\0' is found.
//------------------------------------------------------------
void StrLCD(u8 *ptr)
{
	while(*ptr!='\0')
		CharLCD(*ptr++);
}

//------------------------------------------------------------
//Function: IntLCD
//Purpose :  Display signed integer on LCD.
//Logic:
//    1. Handle zero case
//    2. Handle negative numbers
//    3. Convert integer to ASCII
//    4. Print digits in correct order
//------------------------------------------------------------
void IntLCD(s32 num)
{
	u8 a[10];
	s8 i=0;
	//itoa
	if(num==0)
		CharLCD('0');
	else
	{
		if(num<0)
		{
			num=-num;
			CharLCD('-');
		}
		/* Convert to ASCII digits (reverse order) */
		while(num>0)
		{
			a[i++]=num%10+48;
			num=num/10;
		}
		for(--i;i>=0;i--)
			CharLCD(a[i]);
	}
}

//------------------------------------------------------------
//Function: FltLCD
//Purpose : Display floating-point number (2 decimal places).
//Logic:
//    1. Handle negative sign
//    2. Extract integer part
//    3. Print decimal point
//    4. Extract 2 fractional digits
//------------------------------------------------------------
void FltLCD(f32 val)
{
	u32 num,i;
	if(val<0)
	{
		CharLCD('-');
		val=-val;
	}
	num=val; // Integer part
	IntLCD(num);
	CharLCD('.');
	for(i=0;i<2;i++)
	{
		val=(val-num)*10;
		num=val;
		CharLCD(num+48);
	}
}

//------------------------------------------------------------
//Function: StoreCustCharFont
//Purpose : Store custom character in LCD CGRAM.
//Example LUT: Can be used to create:
//        - Degree symbol (°)
//        - Custom icons
//NOTE: Before writing to CGRAM, 
//      proper CGRAM address must be set.
//------------------------------------------------------------
void StoreCustCharFont(void)
{
	u8 i,LUT[]={0x07,0x09,0x07,0x00,0x00,0x00,0x00,0x00};
	for(i=0;i<8;i++)
		CharLCD(LUT[i]);
	
}
