#include "multiboot2.h"

static volatile unsigned char *video = ( unsigned char * ) 0xB8000;

static void clear( void )
{
    for ( int i = 0; i < 80 * 24 * 2; i ++ )
        video[ i ] = 0;
}

static void putchar( int c )
{
    const int columns = 80;
    const int lines = 24;
    static int x = 0, y = 0;

    if ( c == '\n' || x >= columns )
        x = 0, y++;

    if ( c == '\n' )
        return;

    if ( y >= lines )
        y = 0;

    int idx = ( x + y * columns ) * 2;
    video[ idx ] = c & 0xff;
    video[ idx + 1 ] = 7; /* vga attribute */

    ++ x;
}

void puts( const char *str )
{
    do putchar( *str ); while ( *str++ );
    putchar( '\n' );
}

void main( unsigned long magic, unsigned long addr )
{
    clear();

    if ( magic != MULTIBOOT2_BOOTLOADER_MAGIC )
    {
        puts( "invalid magic number :-(" );
        return;
    }

    if ( addr & 7 )
    {
        puts( "unaligned mbi :-(" );
        return;
    }

    puts( "hello world, i guess?" );
}
