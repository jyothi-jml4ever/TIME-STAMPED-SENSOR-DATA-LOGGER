/*------------------------------------------------------------
File: adc_defines.h
Purpose: Contains clock configuration values and bit definitions
    required for configuring ADC of LPC21xx.
------------------------------------------------------------*/
#ifndef ADC_DEFINES_H
#define ADC_DEFINES_H

#include "RTC_defines.h"

#define FOSC 12000000   //12MHz
//#define CCLK (FOSC*5) //60MHz
//#define PCLK (CCLK/4) //15MHz
#define ADCCLK 3500500 //According to LPC21xx datasheet: ADC clock must be <= 4.5 MHz
#define CLKDIV ((PCLK/ADCCLK)-1) //3

//defines for ADCR sfr
#define CLKDIV_BITS        8 //@8-15
#define PDN_BIT            21
#define ADC_CONV_START_BIT 24

//defines for ADDR sfr
#define DIGITAL_DATA_BITS 6//@6-15
#define DONE_BIT          31


//These values configure corresponding pins for ADC function in PINSEL1.
#define AIN0_PIN_0_27 0x00400000
#define AIN1_PIN_0_28 0x01000000
#define AIN2_PIN_0_29 0x04000000
#define AIN3_PIN_0_30 0x10000000

#define CH0 0
#define CH1 1
#define CH2 2
#define CH3 3
//add mores defines as & when required

#endif
