
#include "kernel/block_allocator.h"
#include "kernel/kernel_const.h"

static block_header_t *free_list = NULL;
static usize MAX_HEAP_AMOUNT = 0; 

void init_malloc(){

    MAX_HEAP_AMOUNT = __HeapLimit - __end__;

    free_list = (block_header_t *)__end__;
    free_list->size = MAX_HEAP_AMOUNT - sizeof(block_header_t);
    free_list->next = NULL;
    free_list->free = true;

}


void *block_malloc(size_t size){

    // keeps block 32-bit aligned
    size = (size + 3) & ~3;
    
    if(size > MAX_HEAP_AMOUNT){
        return NULL;
    }
   
    block_header_t *current = free_list;

    // finds free block that fits the size
    while(current && (current->free == false || current->size < size)){
        current = current->next;
    }

    if(!current || current->size < size)
        return NULL;

    if(current->size >= sizeof(block_header_t) + size + 1){

        block_header_t *new_block = (block_header_t*)((u8*)current + sizeof(block_header_t) + size);

        new_block->size = current->size - size - sizeof(block_header_t);
        new_block->free = true;
        new_block->next = current->next;

        current->size = size;
        current->next = new_block;        

    }

    current->free = false;

    return (void *)((u8 *)current + sizeof(block_header_t));
}



void free_block(void *mem){

    if(!mem)
        return;

    block_header_t *current = (block_header_t*)((u8*)mem - sizeof(block_header_t));
    current->free = true;

    while(current->next && current->next->free){

        current->size += sizeof(block_header_t) + current->next->size;

        current->next = current->next->next;
    }
}
