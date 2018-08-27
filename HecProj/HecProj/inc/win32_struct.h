/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+                                                                   +
+  win32.c - this file has win32 API native code                    +
+                                                                   +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+  macros                                                           +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#pragma once
#include <stdio.h>

#define S1	signed char
#define S2	signed short
#define S4	signed long
#define S8	signed __int64	

#define U1	unsigned char
#define U2	unsigned short
#define U4	unsigned long
#define U8	unsigned __int64

/*
Use ANSI-754 standard for single and double precision floats
single precision = 4 bytes
double precision = 8 bytes
*/

#define F4	float
#define F8	double

/* platform-specific I/O ------------------------------------------*/

#define PRINT_UREG(rstr,reg)	printf("%-6s=%-21I64u",rstr,reg)
#define PRINT_SREG(rstr,reg)	printf("%-6s=%-21I64d",rstr,reg)
#define PRINT_FREG(rstr,reg)	printf("%-6s=%g",rstr,(F4)reg)
#define PRINT_DREG(rstr,reg)	printf("%-6s=%g",rstr,(F8)reg)

#define pU1(arg)	printf("%u",arg)
#define pU2(arg)	printf("%hu",arg)
#define pU4(arg)	printf("%lu",arg)
#define pU8(arg)	printf("%I64lu",arg)

#define pS1(arg)	printf("%d",arg)
#define pS2(arg)	printf("%hd",arg)
#define pS4(arg)	printf("%ld",arg)
#define pS8(arg)	printf("%I64d",arg)

#define PRINT_MEM(index)	printf("RAM[%I64lu]=%u",index,RAM[index])

#define rU8(arg)	scanf("%I64lu",arg) 

#define fpU8(ptr,arg)	fprintf(ptr,"%I64lu",arg)
#define fpS8(ptr,arg)	fprintf(ptr,"%I64d",arg)

/* macros below used during reformating ---------------------------*/

/*
reverse the order of bytes within an array
*/

U1 fb[8];

#define FORMAT_WORD(arr,start)	{ fb[0]=arr[start+1];\
                                  fb[1]=arr[start];\
                                  arr[start]=fb[0];\
                                  arr[start+1]=fb[1]; }

#define FORMAT_DWORD(arr,start)	{ fb[0]=arr[start+3];\
                                  fb[1]=arr[start+2];\
								  fb[2]=arr[start+1];\
								  fb[3]=arr[start];\
                                  arr[start]=fb[0];\
                                  arr[start+1]=fb[1];\
								  arr[start+2]=fb[2];\
								  arr[start+3]=fb[3]; }

#define FORMAT_QWORD(arr,start){ fb[0]=arr[start+7];\
                                  fb[1]=arr[start+6];\
								  fb[2]=arr[start+5];\
								  fb[3]=arr[start+4];\
								  fb[4]=arr[start+3];\
								  fb[5]=arr[start+2];\
								  fb[6]=arr[start+1];\
								  fb[7]=arr[start];\
                                  arr[start]=fb[0];\
                                  arr[start+1]=fb[1];\
								  arr[start+2]=fb[2];\
								  arr[start+3]=fb[3];\
								  arr[start+4]=fb[4];\
								  arr[start+5]=fb[5];\
								  arr[start+6]=fb[6];\
								  arr[start+7]=fb[7]; }

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+  public prototypes                                                +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void checkEndian();
void printBytes(U1 bytes[], int nbytes);
void testConversion();

U2 bytecodeToWord(U1 bytes[]);
U4 bytecodeToDWord(U1 bytes[]);
U8 bytecodeToQWord(U1 bytes[]);
F4 bytecodeToFloat(U1 bytes[]);
F8 bytecodeToDouble(U1 bytes[]);

void wordToBytecode(U2 word, U1 arr[]);
void dwordToBytecode(U4 dword, U1 arr[]);
void qwordToBytecode(U8 qword, U1 arr[]);
void floatToBytecode(F4 flt, U1 arr[]);
void doubleToBytecode(F8 dbl, U1 arr[]);

U4 getAvailableMemory();
U4 getFileSize(char *name);
void testNativeFunctions();