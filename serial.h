#ifndef SERIAL_H
#define SERIAL_H

#define PORT 0x3f8   /* COM1 */

int inb(int port);
void outb(int port, int c);

void init_serial();
int is_transmit_empty();
void write_serial(char a);
int serial_received();;
char read_serial();

#endif