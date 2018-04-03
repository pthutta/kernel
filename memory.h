#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

#define PAGE_TABLES 64
#define PAGE_COUNT ((PAGE_TABLES)*(1024))
#define FRAME_COUNT ((1024)*(1024))
#define INT_SIZE 32
#define NULL ( (void *) 0)

// PAGING

extern unsigned int page_directory[1024] __attribute__((aligned(4096)));
extern unsigned int page_tables[PAGE_TABLES][1024] __attribute__((aligned(4096)));
extern unsigned int bitmap[FRAME_COUNT / INT_SIZE];
extern unsigned int lastAllocatedPage;
extern unsigned int lastAllocatedFrame;

void loadPageDirectory(unsigned int *);

void enablePaging();

void setUpPaging();

void *allocPage();

void freePage();


// DYNAMIC ALLOCATION

typedef struct freeBlock {
    struct freeBlock *next;
    unsigned int size;
} freeBlock;

extern freeBlock *freeList;

freeBlock *getNewBlock();

freeBlock *expand(freeBlock *last);

void *malloc(unsigned int bytes);

void free(void *ptr);

void *memcpy(void *to, void *from, unsigned int size);

void *realloc(void *ptr, unsigned int bytes);

#endif