/*------------------------------------------------------------
File: rtc_defines.h
Purpose: Macro definitions for RTC configuration
------------------------------------------------------------*/
#ifndef RTC_DEFINES_H
#define RTC_DEFINES_H

// System clock and peripheral clock Macros
#define FOSC 12000000 //12MHz
#define CCLK (5*FOSC) //60MHz  
#define PCLK (CCLK/4) //15MHz

// RTC Macros (formulas from data sheet)
#define PREINT_VAL ((PCLK/32768)-1)
#define PREFRAC_VAL (PCLK-(PREINT_VAL+1)*32768)

//CCR register bits (Clock Control Register. Controls the function of the clock divider.)
#define RTC_ENABLE  (1<<0)
#define RTC_RESET   (1<<1)
#define RTC_CLKSRC  (1<<4)

//#define _LPC2148

#endif
