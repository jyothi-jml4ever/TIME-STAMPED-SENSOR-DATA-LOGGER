/*------------------------------------------------------------
File: lm35.h
Purpose: Provides function prototypes to read temperature
         from LM35 sensor using ADC and return the value
         in Celsius or Fahrenheit.
------------------------------------------------------------*/
#ifndef LM35_H
#define LM35_H

#include "types.h"
//void Read_LM35(f32 *tdegC,f32 *tdegF);
f32 Read_LM35(u8 tType);
f32 Read_LM35_NP(u8 tType);

#endif
