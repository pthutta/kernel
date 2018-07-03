#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multiboot2.h"
#include "memory.h"
#include "serial.h"
#include "calls.h"

static volatile unsigned char *video = ( unsigned char * ) 0xB8000;

static void clear( void ) {
    for ( int i = 0; i < 80 * 24 * 2; i ++ )
        video[ i ] = 0;
}

static void putchar_k(int c) {
    const int columns = 80;
    const int lines = 24;
    static int x = 0, y = 0;

    if (c == '\n' || x >= columns)
        x = 0, y++;

    if (c == '\n')
        return;

    if (y >= lines)
        y = 0;

    int idx = (x + y * columns) * 2;
    video[idx] = c & 0xff;
    video[idx + 1] = 7; /* vga attribute */

    ++x;
}

void putsInline(const char *str) {
    do putchar_k(*str); while (*str++);
}

void puts_k(const char *str) {
    putsInline(str);
    putchar_k('\n');
}

void printUInt(unsigned int number) {
    unsigned int a = number;

    if (number > 9) {
        printUInt(number / 10);
    }
    putchar_k('0' + (a % 10));
}

void print(unsigned int number) {
    printUInt(number);
    puts_k("");
}

void check(int val) {
    if (val == 0) {
        puts_k("Fail :(");
    }
    else {
        puts_k("Success :)");
    }
}

void testMemory() {
    int *x = (int *) malloc(sizeof(int));
    *x = 10;
    check(*x == 10);
    print(x);

    x = (int *) realloc(x, 3 * sizeof(int));
    check(*x == 10);

    x = (int *) realloc(x, 2 * sizeof(int));
    check(*x == 10);

    free(x);

    int *y = (int *) malloc(sizeof(int));
    int *z = (int *) malloc(sizeof(int));

    *y = 6;
    *z = 42;

    check(*y == 6);
    check(*z == 42);

    print(y);
    print(z);

    free(z);
    free(y);

    void *large = malloc(4*1024);
    print(large);
    free(large);

    large = malloc(2*4*1024 - 1);
    print(large);
    
    void *small = malloc(12);
    print(small);

    free(large);
    free(small);
}

void printModule(struct multiboot_tag_module *module) {
    char *text = (char *) module->mod_start;

    if (strstr( module->cmdline, "exec" ) == module->cmdline) {
        unsigned int size = module->mod_end - module->mod_start;
        unsigned int address = 0;

        if (!strcmp( module->cmdline, "exec.data" )) {
            address = 0x0180A000;
            putsInline("exec.data");
            
        } else if (!strcmp( module->cmdline, "exec.text" )) {
            address = 0x01800000;
            putsInline("exec.text");
        }

        memcpy((void *) address, (void *) module->mod_start, size);
        if (memcmp((void *) address, (void *) module->mod_start, size) == 0) {
            putsInline("copy successful");
        }
        else {
            putsInline("copy failed");
        }
    }
    else {
        while (text != module->mod_end) {
            putchar_k(*text);
            text++;
        }
    }

    puts_k("");
}

void obtainReservedMemory(struct multiboot_tag_mmap *mmap) {
    multiboot_memory_map_t *entry = mmap->entries;

    while ((unsigned long) entry < (unsigned long) mmap + mmap->size) {
        if (entry->type == MULTIBOOT_MEMORY_RESERVED) {
            for (unsigned long i = entry->addr; i < (unsigned long)(entry->addr + entry->len); ++i) {
                unsigned int frameIndex = (i & (~0xFFF)) / 0x1000;
                bitmap[frameIndex / INT_SIZE] |= (1 << (frameIndex % INT_SIZE));
            }
        }
        entry++;
    }
}

void main(unsigned long magic, unsigned long addr) {
    clear();

    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        puts_k("invalid magic number :-(");
        return;
    }

    if (addr & 7) {
        puts_k("unaligned mbi :-(");
        return;
    }

    init_serial();

    //puts_k("hello world, i guess?");

    unsigned long data = addr + 8;
    struct multiboot_tag *tag = (struct multiboot_tag *) data;

    while (tag->type != MULTIBOOT_TAG_TYPE_END) {
        if (tag->type == MULTIBOOT_TAG_TYPE_MODULE) {
            printModule((struct multiboot_tag_module *) data);
        }
        else if (tag->type == MULTIBOOT_TAG_TYPE_MMAP) {
            obtainReservedMemory((struct multiboot_tag_mmap *) data);
        }

        data += tag->size + 8;
        data &= ~7;

        tag = (struct multiboot_tag *) data;
    }

    setUpPaging();
    testMemory();

    unsigned int moduleAddress = 0x01800000;
    for (int i = 0; i < 1024; ++i)
    {
        page_tables[6][i] = (moduleAddress + i * 0x1000) | 7;
    }
    page_directory[6] = ((unsigned int) page_tables[6]) | 7;

    for (int i = 192; i < 224; ++i)
    {
        bitmap[i] = 0xFFFFFFFF;
    }

    setUpGDT();
    setUpIDT();

    /*for (unsigned int i = 0; i < FRAME_COUNT / INT_SIZE; ++i) {
        if (bitmap[i] != 0) {
            putsInline("reserved: ");
            print(i);
        }
    }*/

    printf("Hello pdclib!\n");
    
    unsigned int userStack = 7*1024*1024*4 - 1;
    runModule(moduleAddress, userStack, &tss[1]);

    printf("Welcome back, to kernel space!\n");

    /*while (1) {
        char c = read_serial();
        putchar_k(c);
        write_serial(c);
    }*/
}
