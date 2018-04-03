#include <stdlib.h>
#include "memory.h"

// PAGING

unsigned int page_directory[1024] __attribute__((aligned(4096)));
unsigned int page_tables[PAGE_TABLES][1024] __attribute__((aligned(4096)));
unsigned int bitmap[FRAME_COUNT / INT_SIZE] = {0};
unsigned int lastAllocatedPage;
unsigned int lastAllocatedFrame;


void setUpPaging() {
    for (int i = 0; i < 1024; ++i) {
        page_directory[i] = 0x00000002; //Supervisor, Write Enabled, Not Present
    }

    for (int i = 0; i < 1024; ++i) {
        page_tables[0][i] = (i * 0x1000) | 3; //Supervisor, Read / Write, Present
        bitmap[i / INT_SIZE] |= (1 << (i % INT_SIZE));
    }
    page_directory[0] = ((unsigned int) page_tables[0]) | 3;

    lastAllocatedPage = 1023;
	lastAllocatedFrame = 1023;

    loadPageDirectory(page_directory);
    enablePaging();
}

void *allocPage() {
    unsigned int frameIndex;
    unsigned int count = 0;
    int isAllocated = 1;

    // search bitmap for free frames
    do {
        frameIndex = (++lastAllocatedFrame) % FRAME_COUNT;
        isAllocated = bitmap[frameIndex / INT_SIZE] & (1 << (frameIndex % INT_SIZE)); // check if bit is set to 0

        count++;
        if (count == FRAME_COUNT) { // free frame not found
            return NULL;
        }

    } while (isAllocated != 0);

    if (lastAllocatedPage >= PAGE_COUNT) { // free page not found
        return NULL;
    }

    bitmap[frameIndex / INT_SIZE] |= (1 << (frameIndex % INT_SIZE)); // set bit to 1 (is allocated)

    lastAllocatedPage++;
    unsigned int pageDirIndex = lastAllocatedPage / 1024;
    unsigned int pageTabIndex = lastAllocatedPage % 1024;

    // first page in page table
    if (pageTabIndex == 0) {
        page_directory[pageDirIndex] = ((unsigned int) page_tables[pageDirIndex]) | 3;
    }

    page_tables[pageDirIndex][pageTabIndex] = (frameIndex * 0x1000) | 3;

    return (void *)((pageDirIndex << 22) | (pageTabIndex << 12));
}

void freePage() {
    unsigned int pageDirIndex = lastAllocatedPage / 1024;
    unsigned int pageTabIndex = lastAllocatedPage % 1024;
    lastAllocatedPage--;

    unsigned int frameIndex = (page_tables[pageDirIndex][pageTabIndex] & (~0xFFF)) / 0x1000;

    bitmap[frameIndex / INT_SIZE] &= ~(1 << (frameIndex % INT_SIZE)); // set bit to 0 (is free)
    page_tables[pageDirIndex][pageTabIndex] = 0x00000000;

    // first page in page table
    if (pageTabIndex == 0) {
        page_directory[pageDirIndex] = 0x00000002;
    }
}

//DYNAMIC ALLOCATION

freeBlock *freeList = NULL;

freeBlock *getNewBlock() {
    void *page = allocPage();
    if (page == NULL) {
        return NULL;
    }

    freeBlock *pageBlock = (freeBlock *) page;
    pageBlock->next = NULL;
    pageBlock->size = 4*1024;
    return pageBlock;
}

freeBlock *expand(freeBlock *last) {
    freeBlock *pageBlock = getNewBlock();
    if (pageBlock == NULL) {
        return NULL;
    }

    if ((unsigned int) last + last->size == pageBlock) { // we can merge last block with the allocated one
        last->size += pageBlock->size;
        last->next = NULL;
        return last;
    }
    else {
        last->next = pageBlock;
        return pageBlock;
    }
}

void *malloc(size_t bytes) {
    // page was not allocated yet or all free blocks were already allocated
    if (freeList == NULL) {
        freeList = getNewBlock();
        if (freeList == NULL) {
            return NULL;
        }
    }

    unsigned int size = bytes + sizeof(freeBlock);

    freeBlock *prevBlock = NULL;
    freeBlock *block = freeList;

    while (block != NULL) {
        if (block->size >= size) {
            freeBlock *nextBlock = NULL;

            if (block->size == size) { // perfect fit
                nextBlock = block->next;
            }
            else { // divide block into two blocks
                nextBlock = (freeBlock *)(((unsigned int) block) + size);
                nextBlock->next = block->next;
                nextBlock->size = block->size - size;

                block->size = size;
                block->next = NULL;
            }

            if (block == freeList) { // block is first node in the free list
                freeList = nextBlock;
            }
            else {
                prevBlock->next = nextBlock;
            }

            return (void *)(block + 1);
        }

        prevBlock = block;
        block = block->next;
    }

    // there is not enough of free space in pages, allocate new one
    if (expand(prevBlock) == NULL) {
        return NULL;
    }
    
    return malloc(bytes);
}

void free(void *ptr) {
    freeBlock *freed = ((freeBlock *) ptr) - 1;
    freeBlock *block = freeList;

    if (freeList == NULL) { // free list is empty, set first node
        freeList = freed;
        return;
    }

    while (!(freed > block && freed < block->next)) { // find fitting place in the free list
        if (freed < block || block->next == NULL) { // freed block should be either first or last
            break;
        }

        block = block->next;
    }
    
    freeBlock *nextBlock;
    if (freed < block) { // freed block belongs before the first node
        nextBlock = block;
        freeList = freed;
    }
    else {
        nextBlock = block->next;
    }

    if ((unsigned int) freed + freed->size == nextBlock) { // we can merge freed block with the next one
        freed->size += nextBlock->size;
        freed->next = nextBlock->next;
    }
    else {
        freed->next = nextBlock;
    }

    if (freed > block) {
        if ((unsigned int) block + block->size == freed) { // we can merge freed block with the previous one
            block->size += freed->size;
            block->next = freed->next;
        }
        else {
            block->next = freed;
        }
    }
}

void *memcpy(void *to, void *from, unsigned int size) {
    char *source = (char *) from;
    char *dest = (char *) to;

    for (int i = 0; i < size; ++i) {
        dest[i] = source[i];
    }

    return to;
}

void *realloc(void *ptr, size_t bytes) {
    if (bytes == 0) {
        free(ptr);
        return NULL;
    }
    if (ptr == NULL) {
        return malloc(bytes);
    }

    freeBlock *block = ((freeBlock *) ptr) - 1;
    unsigned int oldSize = block->size - sizeof(freeBlock);

    if (bytes == oldSize) {
        return ptr;
    }
    else {
        void *newPtr = malloc(bytes);
        if (newPtr != NULL) {
            memcpy(newPtr, ptr, (bytes < oldSize) ? bytes : oldSize);
            free(ptr);
        }
        return newPtr;
    }
}
