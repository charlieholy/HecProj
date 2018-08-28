/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+                                                                   +
+ main.cpp - this is the boot-strap file ���ǿ������ļ�	   	    +
+                                                                   +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ ANSI includes      ��׼����                                       +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ virtual machine includes  ���������                              +
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
+ assembler components   ��װԪ��                                   +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include<common.h>
#include<error.h>
#include<cmdline.h>
#if 0
#include<lnscan.cpp>
#include<strtbl.cpp>
#include<globvar.cpp>
#include<sframe.cpp>
#include<label.cpp>
#include<proc.cpp>
#include<symtbl.cpp>
#include<hashtbl.cpp>
#include<linetok.cpp>
#include<pass1.cpp>
#include<pass2.cpp>
#include<bldfile.cpp>
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

	/*1) handle command line arguments ���������в���*/

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



