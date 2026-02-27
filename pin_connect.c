/*------------------------------------------------------------
File: pin_connect.c
Purpose: Pin function configuration for LPC21xx
------------------------------------------------------------*/
#include<LPC21xx.h> //Header with LPC21xx register definitions
//------------------------------------------------------------
//Function: CfgPinFunc
//Purpose : Configure pin function (GPIO / alternate function)
//------------------------------------------------------------
void CfgPinFunc(int PortNo,int PinNo,int Func)
{
	if(PortNo==0) // Check for Port 0
	{
		if(PinNo<16) // Pins 0–15 use PINSEL0
		{
			PINSEL0=(PINSEL0&~(3<<(PinNo*2))) | (Func<<(PinNo*2)); // Set function
		}
		else // Pins 16–31 use PINSEL1
		{
			PINSEL1=(PINSEL1&~(3<<((PinNo-16)*2))) | (Func<<((PinNo-16)*2)); // Set function
		}
	}
	else
	{
		//dummy
	}
}
