#ifndef KERNEL_BLOCK_ALLOCATOR_H
#define KERNEL_BLOCK_ALLOCATOR_H

#include "kernel/stdtypes.h"

typedef struct block_header_t {
    usize size;
    struct block_header_t *next;
    bool free;
} block_header_t;

void block_init_malloc();
void free_block(void *mem);
void *block_malloc(size_t size);

#endif
