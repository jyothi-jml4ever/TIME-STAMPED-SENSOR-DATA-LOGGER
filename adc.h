/*------------------------------------------------------------
File: adc.h
Purpose: Header file for ADC driver of LPC21xx.
------------------------------------------------------------*/
#ifndef ADC_H
#define ADC_H

#include "types.h"
void Init_ADC(u32 chNo);
void Read_ADC(u32 chNo,f32 *eAR,u32 *adcDVal);

#endif
