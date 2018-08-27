#include<stdio.h>
#include<stdlib.h>

#ifdef WINDOWS_32
#include<win32.c>		
#endif
#ifdef LINUX_x86
#include<linux.c>		
#endif

#define FATAL_ERROR();		exit(1);
#define FATAL_ERROR1(str);	printf(str);exit(1);

#define FCLOSE(arg);	if(fclose(arg)){ printf("could not close executable file\n"); }

//#include<dbgdata.c>


void main(int argc, char *argv[])
{
	
	return;

}/*end main*/

