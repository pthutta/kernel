#ifndef CALLS_H
#define CALLS_H

#include <stdint.h>

#define SEG_DESCTYPE(x)  ((x) << 0x04) // Descriptor type (0 for system, 1 for code/data)
#define SEG_PRES(x)      ((x) << 0x07) // Present
#define SEG_SAVL(x)      ((x) << 0x0C) // Available for system use
#define SEG_LONG(x)      ((x) << 0x0D) // Long mode
#define SEG_SIZE(x)      ((x) << 0x0E) // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x)      ((x) << 0x0F) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_PRIV(x)     (((x) &  0x03) << 0x05)   // Set privilege level (0 - 3)

#define SEG_DATA_RD        0x00 // Read-Only
#define SEG_DATA_RDA       0x01 // Read-Only, accessed
#define SEG_DATA_RDWR      0x02 // Read/Write
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 // Execute-Only
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A // Execute/Read
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed

#define GDT_SIZE 16
#define IDT_SIZE 256

#define SYS_WRITE 0
#define SYS_READ 1


struct gdt_ptr {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__ ((packed));

extern unsigned int tss[26];

void setGdt();
void setTss();
void setIdt(unsigned int *);

uint64_t create_GDT_descriptor(uint32_t base, uint32_t limit, uint16_t flag);
uint64_t create_IDT_descriptor(unsigned short select, unsigned int offset, unsigned short type);

void init_descriptor_tables();
void setUpGDT();
void setUpIDT();
void interruptHandler();
void goBackToKernelSpaceHandler();
void runModule(unsigned int address, unsigned int stack, unsigned int tss1);
int sysCallHandler(int sysCallNum, void * buf, size_t length);

size_t read_k(void * buf, size_t length);
size_t write_k(void * buf, size_t length);

#endif