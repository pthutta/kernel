#ifndef SYSCALLS_H
#define SYSCALLS_H

#define SYS_WRITE 0
#define SYS_READ 1

void sysCall(int sysCallNum, void * buf, size_t length);
void exitToKernel();

#endif