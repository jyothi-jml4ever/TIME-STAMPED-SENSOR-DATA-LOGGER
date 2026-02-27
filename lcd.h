/*------------------------------------------------------------
File: lcd.h
Purpose: LCD Driver Header File, 
         contains function prototypes for controlling
         a 16x2 character LCD module.
------------------------------------------------------------*/
#ifndef LCD_H
#define LCD_H

#include "types.h"
void InitLCD(void);
void CmdLCD(u8);
void CharLCD(u8);	
void DispLCD(u8);
void StrLCD(u8 *);
void IntLCD(s32);
void FltLCD(f32);
void StoreCustCharFont(void);

#endif
