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

	StringTable strTbl;
	HashTable hashTbl(&strTbl);
	SymbolTable symTbl(&strTbl);

	struct Line line;
	{
		Pass1 pass1(&strTbl, &symTbl, &hashTbl);
		LineScanner scanner(&cmdLine);
		line = scanner.getInputLine();
		while (line.end != TRUE)
		{
			pass1.parseLine(&line);
			line = scanner.getInputLine();
		}
		pass1.parseLine(&line);
	}

	if (nErrors > 0)
	{
		printf("%d Error(s) during first pass\n", nErrors);
		printf("build failed\n");
		FATAL_ERROR();
	}

	/*3) PASS2 - create bytecode temp file and listing file */

	MAIN_DEBUG0("initiating second pass\n");
	{
		Pass2 pass2(&cmdLine, &strTbl, &symTbl, &hashTbl);
		LineScanner scanner(&cmdLine);
		line = scanner.getInputLine();
		while (line.end != TRUE)
		{
			pass2.parseLine(&line);
			line = scanner.getInputLine();
		}
		pass2.parseLine(&line);
		if (cmdLine.listing == TRUE) { pass2.generateSymbolSummary(); }
	}
	MAIN_DEBUG1("%lu bytes written to tempfile\n", pass2.bytePosPass2);


	/*if errors exist after 2rd pass, shutdown */

	if (nErrors > 0)
	{
		printf("main(): %d Error(s) during second pass\n", nErrors);
		printf("main(): build failed\n");
		FATAL_ERROR();
	}

	/*4) build compilation unit */

	MAIN_DEBUG0("building bytecode executable\n");
	{
		BuildFile bldfile(&cmdLine, &strTbl, &symTbl);
		bldfile.buildFileFormat();
	}

	/*5) safe-shutdown */

	printf("main(): exiting with (%d) errors\n", nErrors);
	shutDown(SHUTDOWN_OK);
	return;

}/*end main*/

/* ----------------------------------------------------------------*/

void shutDown(U1 code)
{
	exit(code);

}/*end shutDown*/



