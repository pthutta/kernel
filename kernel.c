#include "multiboot2.h"
#include "memory.h"

#define PORT 0x3f8   /* COM1 */

static volatile unsigned char *video = ( unsigned char * ) 0xB8000;

int inb(int port);
void outb(int port, int c);

void init_serial() {
   outb(PORT + 1, 0x00);    // Disable all interrupts
   outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(PORT + 1, 0x00);    //                  (hi byte)
   outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

static void clear( void ) {
    for ( int i = 0; i < 80 * 24 * 2; i ++ )
        video[ i ] = 0;
}

int is_transmit_empty() {
   return inb(PORT + 5) & 0x20;
}
 
void write_serial(char a) {
   while (is_transmit_empty() == 0);
 
   outb(PORT,a);
}

int serial_received() {
   return inb(PORT + 5) & 1;
}
 
char read_serial() {
   while (serial_received() == 0);
 
   return inb(PORT);
}

static void putchar(int c) {
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
    do putchar(*str); while (*str++);
}

void puts(const char *str) {
    putsInline(str);
    putchar('\n');
}

void printUInt(unsigned int number) {
    unsigned int a = number;

    if (number > 9) {
        printUInt(number / 10);
    }
    putchar('0' + (a % 10));
}

void print(unsigned int number) {
    printUInt(number);
    puts("");
}

void check(int val) {
    if (val == 0) {
        puts("Fail :(");
    }
    else {
        puts("Success :)");
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

void main(unsigned long magic, unsigned long addr) {
    clear();

    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        puts("invalid magic number :-(");
        return;
    }

    if (addr & 7) {
        puts("unaligned mbi :-(");
        return;
    }

    init_serial();

    //puts("hello world, i guess?");

    unsigned long data = addr + 8;
    struct multiboot_tag *tag = (struct multiboot_tag *) data;

    while (tag->type != MULTIBOOT_TAG_TYPE_END) {
        if (tag->type == MULTIBOOT_TAG_TYPE_MODULE) {
            struct multiboot_tag_module *module = (struct multiboot_tag_module *) data;

            char *text = (char *) module->mod_start;
            while (text != module->mod_end) {
                putchar(*text);
                text++;
            }

            puts("");
        }

        data += tag->size + 8;
        data &= ~7;

        tag = (struct multiboot_tag *) data;
    }

    setUpPaging();
    testMemory();

    while (1) {
        char c = read_serial();
        putchar(c);
        write_serial(c);
    }
}
