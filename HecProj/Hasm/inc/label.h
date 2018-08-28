/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+                                                                   +
+ label.cpp - metadata for labels               	  		        +
+                                                                   +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ decalaration                                                      + 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#pragma once
#include "win32_struct.h"

struct Label
{
	U8 text;		/* index into StrTbl of where identifier begins */
	U8 address;		/* address of label*/
	U4 line;		/* source code line containing declaration */
};





