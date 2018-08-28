/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+                                                                   +
+ sframe.cpp - stack frame elements                                 +
+              metadata for ret val, args, locals 	  		        +
+                                                                   +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ decalaration                                                      + 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#pragma once
#include "win32_struct.h"


struct StackFrame
{
	U8 text;		/* index into StrTbl of where identifier begins */
	S4 fpOffset;	/* +n or -n from $FP */
	U4 line;		/* source code line containing declaration */
};







