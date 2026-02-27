/*------------------------------------------------------------
File: defines.h
Purpose: Provides commonly used bit manipulation macros.
------------------------------------------------------------*/
#ifndef DEFINES_H
#define DEFINES_H

#define SETBIT(WORD,BP) WORD|=(1<<BP)
#define CLRBIT(WORD,BP) WORD&=~(1<<BP)
#define CPLBIT(WORD,BP) WORD^=(1<<BP)
#define WRITEBIT(WORD,BP,BIT) WORD=(WORD&~(1<<BP))|(BIT<<BP)
#define WRITENIBBLE(WORD,SBP,NIBBLE) WORD=(WORD&~(0X0f))|(NIBBLE<<SBP)
#define WRITEBYTE(WORD,SBP,BYTE) WORD=(WORD&~(0Xff))|(BYTE<<SBP)
#define WRITEHWORD(WORD,SBP,HWORD) WORD=(WORD&~(0X0fff))|(HWORD<<SBP)
#define WRITEFWORD(WORD,SBP,FWORD) WORD=(WORD&~(0Xffff))|(FWORD<<SBP)

#define READBIT(WORD,BP) ((WORD>>BP)&1)

#endif
