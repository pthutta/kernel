/* _PDCLIB_fileops

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST
#include <stdio.h>
#include <stdint.h>
#include <_PDCLIB_glue.h>
#include <errno.h>
#include <user/syscall.h>

static bool readf( _PDCLIB_fd_t self, void * buf, size_t length, 
                   size_t * numBytesRead )
{
    sysCall(SYS_READ, buf, length);
    *numBytesRead = length;
    return true;
}

static bool writef( _PDCLIB_fd_t self, const void * buf, size_t length, 
                   size_t * numBytesWritten )
{
    sysCall(SYS_WRITE, buf, length);
    *numBytesWritten = length;
    return true;
}
static bool seekf( _PDCLIB_fd_t self, int_fast64_t offset, int whence,
    int_fast64_t* newPos )
{
    errno = ENOTSUP;
    return false;
}

static void closef( _PDCLIB_fd_t self )
{
    errno = ENOTSUP;
}

const _PDCLIB_fileops_t _PDCLIB_fileops = {
    .read  = readf,
    .write = writef,
    .seek  = seekf,
    .close = closef,
};

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    // Tested by stdio test cases
    return TEST_RESULTS;
}

#endif
