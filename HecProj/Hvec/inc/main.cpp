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

#include<common.c>		/* universal elements --普遍要素-------*/
#ifdef WINDOWS_32
#include<win32.c>		/* mapping VM data types to native types VM的数据类型映射到本地类型--*/
#endif
#ifdef LINUX_x86
#include<linux.c>		/* mapping VM data types to native types --*/
#endif
#include<iset.c>		/* instruction set ---指令集----------*/
#include<exenv.c>		/* registers, RAM ---寄存器，存储器--------*/
#include<error.c>		/* handle errors ----处理错误-----------*/

#include<cmdline.c>		/* handle command line -----处理命令行-----*/
#include<dbgdata.c>		/* loads debug data-structures ---负荷调试数据结构---*/
#include<init.c>		/* code for loading bytecode into RAM --代码加载到RAM的字节码---*/
#include<reformat.c>	/* change big-endian to native and verify 改变大端字节序，以本地和核查-*/

#ifdef WINDOWS_32		/* instruction execution --指令执行----*/
#include<intwin32.c>
#endif
#ifdef LINUX_x86		/* instruction execution --指令执行-------*/
#include<intlinux.c>
#endif
#include<load.c>
#include<store.c>
#include<pushpop.c>
#include<move.c>
#include<jump.c>
#include<bitwise.c>
#include<shift.c>
#include<intmath.c>
#include<fltmath.c>
#include<dblmath.c>
#include<interupt.c>

#include<dbgcmd.c>
#include<run.c>

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

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ public prototypes                                                 +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void main(int argc, char *argv[]);

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ function definitions                                              +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void main(int argc, char *argv[])
{
	struct CmdLine cl;

	/*1) establishing error log */

	DBG_MAIN0("1) establishing error log\n");
	setUpErrorFile();

	/*2) handle command line arguments, set computer switches */

	DBG_MAIN0("2) invoking handleArguments()\n");
	cl = handleArguments(argc,argv);
	if(cl.ok==FALSE)
	{
		FATAL_ERROR1("main(): errors during handleArguments()");
	}

	/*3) init execution environment and load bytecode */

	DBG_MAIN0("3) invoking initHEC()\n");
	RAM = NULL;
	if(initHEC(cl)==FALSE)
	{
		FATAL_ERROR1("main(): errors during initHEC()");
	}

	/*4) re-format numeric operands to native and verify */

	DBG_MAIN0("4) invoking reformat()\n");
	if(reformat()==FALSE)
	{
		FATAL_ERROR1("main(): errors during reformat()");
	}

	/*5) begin execution*/

	DBG_MAIN0("5) invoking run()\n");
	run(cl.debug);

	/*6) safe-shutdown*/

	DBG_MAIN0("6) HEC VM shutting down via HALT instruction\n");
	shutDown(SHUTDOWN_OK);
	return;

}/*end main*/
