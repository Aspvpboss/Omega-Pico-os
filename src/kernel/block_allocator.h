#ifndef KERNEL_BLOCK_ALLOCATOR_H
#define KERNEL_BLOCK_ALLOCATOR_H

#include "kernel/stdtypes.h"

typedef struct block_header_t {
    usize size;
    struct block_header_t *next;
    bool free;
} block_header_t;

void block_init_malloc();
void block_free(void *mem);
void *block_malloc(size_t size);

// returns num bytes of allocated memory
usize block_allocated_memory();

// returns num bytes of available memory
usize block_available_memory();

#endif
