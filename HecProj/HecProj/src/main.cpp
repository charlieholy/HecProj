#include <stdio.h>
#include "list.h"
void main() {
	List list(4, 4);

	list.addToList(4);
	list.addToList(-5);
	list.addToList(1);
	list.addToList(11);

	list.addToList(7);
	list.addToList(8);
	list.addToList(-12);
	list.addToList(122);

	list.addToList(4);
	list.addToList(5);
	list.addToList(5);
	list.addToList(-101);

	list.addToList(3);

	list.printList();

	printf("list[2]=%d\n", list.ptr[2]);
	return;
}