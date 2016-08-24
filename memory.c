#include "header.h"

uint32_t end_of_heap = 0;
uint32_t start_of_heap = 0;

void init_heap(uint32_t start, uint32_t end) {
    start_of_heap = start;
    end_of_heap = end;
}

void* kmalloc(uint32_t nbytes) {
    if (start_of_heap + nbytes >= end_of_heap)
        return NULL;
    uint32_t temp = start_of_heap;
    start_of_heap += nbytes;
    return (void*)temp;
}

void kfree(void *ptr) {
    UNUSED(ptr);
    // TODO: does nothing for now
}