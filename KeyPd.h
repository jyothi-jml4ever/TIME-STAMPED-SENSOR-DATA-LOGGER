/*------------------------------------------------------------
File: KeyPd.h
Purpose: Header file for 4x4 Matrix Keypad driver.
------------------------------------------------------------*/
#ifndef KEYPD_H
#define KEYPD_H

#include"types.h"
void KeyPdInit(void);
u8 ColStat(void);
u8 KeyVal(void);

#endif
