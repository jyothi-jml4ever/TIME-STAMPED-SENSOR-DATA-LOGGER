/*------------------------------------------------------------
File: KeyPdDefines.h
Purpose: Defines hardware connections and key mapping
         for 4x4 Matrix Keypad.

Keypad Type:
    4 Rows × 4 Columns = 16 Keys

Working Principle:
    - Rows are configured as OUTPUT
    - Columns are configured as INPUT
    - One row is driven LOW at a time
    - Columns are scanned to detect key press
------------------------------------------------------------*/
#ifndef KEYPDDEFINES_H
#define KEYPDDEFINES_H

#include<LPC21xx.h>
#include"types.h"
/*------------------------------------------------------------
  Row Pin Definitions (Port 1)
  R0 -> P1.19
  R1 -> P1.20
  R2 -> P1.21
  R3 -> P1.22
  These pins are set as OUTPUT during scanning.
------------------------------------------------------------*/
#define R0 19
#define R1 20
#define R2 21
#define R3 22

/*------------------------------------------------------------
  Column Pin Definitions (Port 1)
  C0 -> P1.23
  C1 -> P1.24
  C2 -> P1.25
  C3 -> P1.26
  These pins are set as INPUT.
  If any column reads LOW when a row is LOW,
  that key is pressed.
------------------------------------------------------------*/
#define C0 23
#define C1 24
#define C2 25
#define C3 26

/*------------------------------------------------------------
  Key Lookup Table (LUT)
  Maps row & column combination to key value.
  Layout Representation:
        C0   C1   C2   C3
  R0    0    1    2    3
  R1    4    5    6    7
  R2    8    9   10   11
  R3   12   13   14   15
  Example: If R2 & C1 detected -> LUT[2][1] = 9
  Used by KeyVal() function to return corresponding key number.
------------------------------------------------------------*/
u8 LUT[][4]={0,1,2,3,
	           4,5,6,7,
			       8,9,10,11,
            12,13,14,15};

#endif
				