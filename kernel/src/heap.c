#include "heap.h"

#define HEAP_START 0x10000
#define HEAP_SIZE 0x10000

static size_t heap_offset;

void heap_init(void) {
        heap_offset = 0;
}

void* malloc(size_t size) {
        if (heap_offset + size > HEAP_SIZE)
                return NULL;

        void* ptr = (void*)(HEAP_START + heap_offset);

        heap_offset += size;

        return ptr;
}