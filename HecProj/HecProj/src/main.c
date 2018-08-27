/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+                                                                   +
+ main.c - this is the boot-strap file which conatins the entry     +
+          exit point of the HEC engine                             +
+          这是启动文件conatins带入境出境点的HEC引擎               +                                                          +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ includes                                                          +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include<stdio.h>		/* ANSI C includes ------------------------*/
#include<stdlib.h>
#include<time.h>

#include<common.h>		/* universal elements --普遍要素-------*/
#ifdef WINDOWS_32
#include<win32.c>		/* mapping VM data types to native types VM的数据类型映射到本地类型--*/
#endif
#ifdef LINUX_x86
#include<linux.c>		/* mapping VM data types to native types --*/
#endif
#include<iset.h>		/* instruction set ---指令集----------*/
#include<exenv.h>		/* registers, RAM ---寄存器，存储器--------*/
#include<error.h>		/* handle errors ----处理错误-----------*/

#ifdef WINDOWS_32		/* instruction execution --指令执行----*/
#include<intwin32.c>
#endif
#ifdef LINUX_x86		/* instruction execution --指令执行-------*/
#include<intlinux.c>
#endif

/*#include<test.c>*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ macros             宏                                             +
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
