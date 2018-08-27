#include <stdio.h>

unsigned char flag = 0;
void alert(unsigned char *ptr);
void main() {
	int i;
	unsigned char breakpoint = 0xCC;
	unsigned char *sptr;
	unsigned char *eptr;
	unsigned char *cptr;
start:
	__asm
	{
		LEA EAX, start
		MOV sptr, EAX
		LEA EAX, end
		MOV eptr, EAX
	}
	cptr = sptr;
	while (cptr < eptr)
	{
		if (*cptr == breakpoint) {
			alert(cptr);
		}
		cptr++;
	}
	printf("do some work..start and end label");
	i++;
end:
	if (flag) { printf("breakpoint found\n"); }
	else { printf("no breakpoints\n");}
	return;
	
}
void alert(unsigned char *ptr)
{
	printf("a break point exist\n");
	printf("address %1X\n", ptr);
	flag = 1;
	return;
}