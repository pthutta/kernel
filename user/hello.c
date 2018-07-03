#include <stdio.h>
#include "syscall.h"

int main();

void _start() {
	main();
	exitToKernel();
}

int main() {
	printf("Hello userland! I am in ring %d\n", 3);
	return 0;
}