/*------------------------------------------------------------
File: uart.h
Purpose: Header file for UART driver functions
------------------------------------------------------------*/
#ifndef UART_H
#define UART_H

#include"types.h"
void InitUART(void);
void UARTTxChar(s8);
void UARTTxStr(s8 *);
s8 UARTRxChar(void);
void UARTTxU32(u32);
void UARTTxF32(f32);
void UARTTx_SendRTC(void);

#endif
