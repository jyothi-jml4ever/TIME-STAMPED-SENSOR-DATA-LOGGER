/*------------------------------------------------------------
File: adc.c
Purpose: Implements ADC initialization and reading functions
    for LPC21xx microcontroller.
ADC Working Summary:
    1. Configure pin as analog input
    2. Configure ADC clock
    3. Enable ADC module
    4. Select channel
    5. Start conversion
    6. Wait for DONE bit
    7. Read digital value
    8. Convert to voltage
------------------------------------------------------------*/

#include "types.h"       //User-defined data type definitions (type aliasing)
#include "delay.h"       //Provides software delay function declarations.
#include <LPC21xx.h>     //Header with LPC21xx register definitions
#include "ADC_defines.h" //Contains clock configuration values and bit definitions
                         //required for configuring ADC of LPC21xx.

/*------------------------------------------------------------
Array: adcChSel[]
Purpose: Stores PINSEL1 bit masks for AIN0–AIN3.
Usage: adcChSel[CH0] -> Configures P0.27 as AIN0
       adcChSel[CH1] -> Configures P0.28 as AIN1
------------------------------------------------------------*/
u32 adcChSel[4]={AIN0_PIN_0_27,
                 AIN1_PIN_0_28,
                 AIN2_PIN_0_29,
                 AIN3_PIN_0_30
                };

//------------------------------------------------------------
//Function: Init_ADC
//Purpose : Initialize ADC module for selected channel.
//------------------------------------------------------------
void Init_ADC(u32 chNo)
{
	//clear prev cfgs of p0.27-p0.30
	PINSEL1&=~(adcChSel[chNo]);
	//cfg req p0.27-p0.30 as AIN0-AIN3 pins
	PINSEL1|=adcChSel[chNo];
	//cfg ADCR
	ADCR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
}

//------------------------------------------------------------
//Function: Read_ADC
//Purpose : Perform ADC conversion and return:
//            - Digital ADC value (0–1023)
//            - Equivalent Analog Voltage
//------------------------------------------------------------
void Read_ADC(u32 chNo,f32 *eAR,u32 *adcDVal)
{
	//clear any previous channel selection
	ADCR&=0xFFFFFF00;
	
	//update req chNo,& start conv
	ADCR|=((1<<ADC_CONV_START_BIT)|(1<<chNo));
	//wait for conv time
	delay_us(3);
	//check if conv completed successfully
	while(((ADDR>>DONE_BIT)&1)==0);
	//stop adc conversion
	ADCR&=~(1<<ADC_CONV_START_BIT);
	
	//read digital data
	*adcDVal=((ADDR>>DIGITAL_DATA_BITS)&1023);
	
	*eAR=*adcDVal * (3.3/1023);
}
