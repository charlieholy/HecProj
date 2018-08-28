/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+                                                                   +
+ main.cpp - this is the boot-strap file 这是开机带文件	   	    +
+                                                                   +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ ANSI includes      标准包括                                       +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ virtual machine includes  虚拟机包括                              +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifdef WINDOWS_32
#include<win32.c>
#endif
#ifdef LINUX_x86
#include<linux.c>
#endif

#include<iset.h>
#include<exenv.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ prototypes                                                        +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void main(int argc, char *argv[]);
void shutDown(U1 code);

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ assembler components   组装元件                                   +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include<common.h>
#include<error.h>
#include<cmdline.h>
#if 1
#include<lnscan.h>
#include<strtbl.h>
#include<globvar.h>
#include<sframe.h>
#include<label.h>
#include<proc.h>
#include<symtbl.h>
#include<hashtbl.h>
#include<linetok.h>
#include<pass1.h>
#include<pass2.h>
#include<bldfile.h>
#endif
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ macros                                                            +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*#define MAIN_DEBUG		1*/

#ifdef	MAIN_DEBUG
#define	MAIN_DEBUG0(arg);				printf("main(): ");printf(arg);
#define MAIN_DEBUG1(arg1,arg2);			printf("main(): ");printf(arg1,arg2);
#define MAIN_DEBUG2(arg1,arg2,arg3);	printf("main(): ");printf(arg1,arg2,arg3);
#else
#define	MAIN_DEBUG0(arg);
#define MAIN_DEBUG1(arg1,arg2);
#define MAIN_DEBUG2(arg1,arg2,arg3);
#endif

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ function definitions                                              +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void main(int argc, char *argv[])
{
	CommandLine cmdLine(&maxErrors);
	nErrors = 0;

	/*1) handle command line arguments 处理命令行参数*/

	MAIN_DEBUG0("handling arguments\n");

	if((cmdLine.handleArgs(argc,argv))==FALSE)
	{
		FATAL_ERROR();
	}

	/*2) PASS1 -  scan, parse, populate symbol table*/

	MAIN_DEBUG0("initiating first pass\n");



}/*end main*/

/* ----------------------------------------------------------------*/

void shutDown(U1 code)
{
	exit(code);

}/*end shutDown*/



