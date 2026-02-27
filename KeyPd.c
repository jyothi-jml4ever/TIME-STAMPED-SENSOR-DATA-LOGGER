/*------------------------------------------------------------
File: KeyPd.c
Purpose: Implements 4x4 Matrix Keypad scanning for LPC21xx.

Working Principle:
    - Rows -> OUTPUT
    - Columns -> INPUT (with pull-up)
    - One row driven LOW at a time
    - If key pressed -> corresponding column becomes LOW
    - LUT[row][col] gives key value
------------------------------------------------------------*/

#include<LPC21xx.h> //Header with LPC21xx register definitions
#include"KeyPdDefines.h" // Row/Column definitions + LUT

//------------------------------------------------------------
//Function: KeyPdInit
//Purpose : Configure keypad GPIO directions.
//How it works:
//    - Set row pins as OUTPUT
//    - Keep all rows LOW initially
//Why LOW?
//    System idle state.
//    During scanning we will selectively control rows.
//------------------------------------------------------------
void KeyPdInit(void)
{
		IODIR1|=((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));
	    //P1.16-P1.19 are for output functionality
		IOCLR1=((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));
		//Initializing rows to 0
}

//------------------------------------------------------------
//Function: ColStat
//Purpose : Detect if any key is pressed.
//How it works:
//    - Reads column bits (P1.23–P1.26)
//    - If all bits HIGH (0x0F) -> no key pressed
//    - If any bit LOW -> key pressed
//Return:
//    1 -> No key pressed
//    0 -> Key pressed detected
//------------------------------------------------------------
u8 ColStat(void)
{
	if((((IOPIN1>>23)&0x0f)==0x0f))
		return 1; // No key pressed
	else 
		return 0; // key pressed
}

//------------------------------------------------------------
//Function: KeyVal
//Purpose : Identify which key is pressed.
//------------------------------------------------------------
u8 KeyVal(void)
{
		char row_val=0,col_val=0;
		IOCLR1=(1<<R0);
		IOSET1=((1<<R1)|(1<<R2)|(1<<R3));
		if((((IOPIN1>>23)&0x0f)!=0x0f))
		{
			row_val=0;
			goto colcheck;
		}
		IOCLR1=(1<<R1);
		IOSET1=((1<<R0)|(1<<R2)|(1<<R3));
		if((((IOPIN1>>23)&0x0f)!=0x0f))
		{
			row_val=1;
			goto colcheck;
		}
		IOCLR1=(1<<R2);
		IOSET1=((1<<R0)|(1<<R1)|(1<<R3));
		if((((IOPIN1>>23)&0x0f)!=0x0f))
		{
			row_val=2;
			goto colcheck;
		}
		IOCLR1=(1<<R3);
		IOSET1=((1<<R0)|(1<<R1)|(1<<R2));
		if((((IOPIN1>>23)&0x0f)!=0x0f))
			row_val=3;
		
		colcheck:		
		if(((IOPIN1>>C0)&1)==0)
			col_val=0;
		else if(((IOPIN1>>C1)&1)==0)
			col_val=1;
		else if(((IOPIN1>>C2)&1)==0)
			col_val=2;
		else
			col_val=3;

		IOCLR1=((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));
	//Initializing rows to 0

		return(LUT[row_val][col_val]);
}
