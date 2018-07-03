#include <stdio.h>
#include "calls.h"
#include "memory.h"

uint64_t gdt[GDT_SIZE] = {0};
struct gdt_ptr gdtr;
struct idt_ptr idtr;
unsigned int tss[26] = {0};
uint64_t idt[IDT_SIZE] = {0};

void init_descriptor_tables()
{
    setUpGDT();
    setUpIDT();
}

uint64_t create_GDT_descriptor(uint32_t base, uint32_t limit, uint16_t flag) {
    uint64_t descriptor;
 
    // Create the high 32 bit segment
    descriptor  =  limit       & 0x000F0000;         // set limit bits 19:16
    descriptor |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
    descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    descriptor |=  base        & 0xFF000000;         // set base bits 31:24
 
    // Shift by 32 to allow for low part of segment
    descriptor <<= 32;
 
    // Create the low 32 bit segment
    descriptor |= base  << 16;                       // set base bits 15:0
    descriptor |= limit  & 0x0000FFFF;               // set limit bits 15:0
 
    return descriptor;
}

void setUpGDT() {
	gdtr.limit = sizeof(uint64_t) * GDT_SIZE - 1;
	gdtr.base = (unsigned int)&gdt;

	//tss[1] = allocPage() + (PAGE_SIZE - 1);
	tss[2] = 0x10;
	tss[25] = (104 << 16);

	gdt[0] = create_GDT_descriptor(0, 0, 0);
	gdt[1] = create_GDT_descriptor(0, 0xFFFFFFFF, SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_PRIV(0) | SEG_CODE_EXRD | SEG_GRAN(1) | SEG_SIZE(1));
	gdt[2] = create_GDT_descriptor(0, 0xFFFFFFFF, SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_PRIV(0) | SEG_DATA_RDWR | SEG_GRAN(1) | SEG_SIZE(1));
	gdt[3] = create_GDT_descriptor(0, 0xFFFFFFFF, SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_PRIV(3) | SEG_CODE_EXRD | SEG_GRAN(1) | SEG_SIZE(1));
    gdt[4] = create_GDT_descriptor(0, 0xFFFFFFFF, SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_PRIV(3) | SEG_DATA_RDWR | SEG_GRAN(1) | SEG_SIZE(1));
    gdt[5] = create_GDT_descriptor((unsigned int) tss, 26 * sizeof(unsigned int), 0xC089);

	setGdt();
	setTss();
}

uint64_t create_IDT_descriptor(unsigned short select, unsigned int offset, unsigned short type) {
    uint64_t descriptor = offset >> 16;
    descriptor <<= 48;
    descriptor |= ((uint64_t)1 << 47);
    descriptor |= ((uint64_t)3 << 45);
    descriptor |= ((uint64_t)type << 40);
    descriptor |= (select << 16);
    descriptor |= (offset & 0xffff);

    return descriptor;
}

void setUpIDT() {
	idtr.limit = sizeof(uint64_t) * IDT_SIZE - 1;
	idtr.base = (unsigned int)&(idt[0]);

    idt[128] = create_IDT_descriptor(0x08, &interruptHandler, 0xe);
    idt[142] = create_IDT_descriptor(0x08, &goBackToKernelSpaceHandler, 0xe);

	setIdt((unsigned int) &idtr); 

    /*printf("TSS[1]: %u\n", tss[1]);
    printf("TSS[2]: %u\n", tss[2]);
    printf("TSS[25]: %u\n", tss[25]);

    printf("GDT: %u\n", gdt);
    printf("GDT[0]: %llu\n", gdt[0]);
    printf("GDT[1]: %llu\n", gdt[1]);
    printf("GDT[2]: %llu\n", gdt[2]);
    printf("GDT[3]: %llu\n", gdt[3]);

    printf("IDT: %u\n", idt);
    printf("IDT[128]: %llu\n", idt[128]);
    printf("intHandler: %u\n", &interruptHandler);*/
}

size_t write_k(void * buf, size_t length) {
    const char *str = (const char *) buf;
    for (int i = 0; i < length; ++i)
    {
        write_serial(str[i]);
    }
    return length;
}

size_t read_k(void * buf, size_t length) {
    char *str = (char *) buf;
    for (int i = 0; i < length; ++i)
    {
        str[i] = read_serial();
    }
    return length;
}

int sysCallHandler(int sysCallNum, void * buf, size_t length) {
    switch (sysCallNum) {
        case SYS_WRITE:
            return write_k(buf, length);

        case SYS_READ:
            return read_k(buf, length);

        default:
            return -1;
    }
}