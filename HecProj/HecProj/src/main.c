/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+                                                                   +
+ main.c - this is the boot-strap file which conatins the entry     +
+          exit point of the HEC engine                             +
+          ���������ļ�conatins���뾳�������HEC����               +                                                          +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ includes                                                          +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include<stdio.h>		/* ANSI C includes ------------------------*/
#include<stdlib.h>
#include<time.h>

#include<common.h>		/* universal elements --�ձ�Ҫ��-------*/
#ifdef WINDOWS_32
#include<win32.c>		/* mapping VM data types to native types VM����������ӳ�䵽��������--*/
#endif
#ifdef LINUX_x86
#include<linux.c>		/* mapping VM data types to native types --*/
#endif
#include<iset.h>		/* instruction set ---ָ�----------*/
#include<exenv.h>		/* registers, RAM ---�Ĵ������洢��--------*/
#include<error.h>		/* handle errors ----�������-----------*/

#ifdef WINDOWS_32		/* instruction execution --ָ��ִ��----*/
#include<intwin32.c>
#endif
#ifdef LINUX_x86		/* instruction execution --ָ��ִ��-------*/
#include<intlinux.c>
#endif

/*#include<test.c>*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ macros             ��                                             +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*#define DBG_MAIN		1*/

#ifdef DBG_MAIN
#define DBG_MAIN0(str)				printf("main(): "); printf(str);
#define DBG_MAIN1(str,arg1)			printf("main(): "); printf(str,arg1);
#define DBG_MAIN2(str,arg1,arg2)	printf("main(): "); printf(str,arg1,arg2);
#else
#define DBG_MAIN0(str)
#define DBG_MAIN1(str,arg1)
#define DBG_MAIN2(str,arg1,arg2)
#endif


void main(int argc, char *argv[])
{
	

}/*end main*/
