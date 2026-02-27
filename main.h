/*------------------------------------------------------------
File: main.h
Purpose: Header file for main application functions
------------------------------------------------------------*/
#ifndef MAIN_H
#define MAIN_H

#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "defines.h"

#include "lcd.h"
#include "rtc_defines.h"
#include "rtc.h"
#include "uart.h"
#include "adc_defines.h"
#include "adc.h"
#include "lm35.h"
#include "KeyPd.h"

/* Hardware Pins */
#define LED     17 //P1.17
#define BUZZER  18 //P1.18
#define SW      16 //P1.16

/* Keypad */
#define KP_BACKSPACE   10
#define KP_ENTER       11

/* Functions */
void Info_On_UART(void);
void Info_On_LCD(void);
void ALERT_Info_On_UART(void);

void MAIN_MENU(void);
void RTC_MENU(void);

void Edit_RTC_Info(void);
u8   GetDayFromDate(void);
u32  Num_from_KeyPd(u8 max_digits);
void EDIT_SP(void);

#endif
