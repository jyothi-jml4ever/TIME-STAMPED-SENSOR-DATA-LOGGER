/*------------------------------------------------------------
File: lm35.c
Purpose: Implements LM35 temperature reading functions.
         This file reads analog voltage from LM35 sensor
         using ADC and converts it into temperature.
------------------------------------------------------------*/
#include "types.h"       //User-defined data type definitions (type aliasing)
#include "adc.h"         //Header file for ADC driver of LPC21xx.
#include "adc_defines.h" //Contains clock configuration values and bit definitions
                         //required for configuring ADC of LPC21xx.

//------------------------------------------------------------
//Function: Read_LM35
//Purpose : Reads temperature from LM35 sensor connected to ADC CH1.
//Working Flow:
//    1. Read ADC channel value (digital + equivalent voltage).
//    2. Convert voltage to temperature.
//    3. Convert to Celsius or Fahrenheit based on input.
//    4. Return final temperature value.

//LM35 Theory:
//    LM35 output = 10mV per °C
//    So,
//       1°C  = 0.01V
//       Temp = Voltage * 100
//------------------------------------------------------------
f32 Read_LM35(u8 tType)
{
	u32 adcDVal; //Stores digital ADC value
	f32 eAR; // Equivalent Analog Reading (Voltage)
  f32 tDeg; // Final temperature value in degree
	
	/* Read ADC Channel 0
       - adcDVal -> digital ADC result
       - eAR     -> converted voltage value */
	Read_ADC(CH0,&eAR,&adcDVal);
	
	/* Convert Voltage to Temperature
       Since LM35 gives 10mV per °C:
       Temperature = Voltage * 100 */
	tDeg=eAR * 100;
	
	//Check required temperature type
	if(tType=='C'); // Do nothing, already in Celsius
	else if(tType=='F')
		tDeg=((tDeg * (9/5.0))+32); // Convert Celsius to Fahrenheit
	return tDeg; //Return final temperature in degree Celsius
}

//------------------------------------------------------------
//Function: Read_LM35_NP
//Purpose : Reads temperature using two ADC channels:

//        CH0 -> Positive terminal
//        CH1 -> Negative terminal

//    Calculates differential temperature:
//        Temperature = (Vpositive - Vnegative) * 100

//Flow:
//    1. Read CH0 voltage.
//    2. Read CH1 voltage.
//    3. Subtract both voltages.
//    4. Convert into temperature.
//    5. Convert to °F if required.
//------------------------------------------------------------
f32 Read_LM35_NP(u8 tType)
{
	  u32 adcDVal1, adcDVal2;   // Raw ADC digital values
    f32 eAR1, eAR2;          // Voltage readings
    f32 tDeg;                // Final temperature

    Read_ADC(CH0, &eAR1, &adcDVal1); //Read Positive terminal (CH0)
    Read_ADC(CH1, &eAR2, &adcDVal2); //Read Negative terminal (CH1)

    /* Calculate voltage difference
       If eAR1 > eAR2 -> Positive temperature
       If eAR1 < eAR2 -> Negative temperature */
    tDeg = (eAR1 - eAR2) * 100;
    
	  if(tType=='C');	
    else if (tType == 'F')
    {
        tDeg = ((tDeg*(9.0/5.0))+32); // Convert to Fahrenheit if required
    }
    return tDeg; // Return temperature difference
}
