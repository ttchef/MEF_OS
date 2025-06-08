
#ifndef MEMORY_H
#define MEMORY_H 

extern char __heap_start;
extern char __heap_end;

#define HEAP_SIZE (__heap_end - __heap_start)

extern char* memory_heap;

#define GPU_CACHED_BASE 0x40000000
#define GPU_UNCACHED_BASE 0xC0000000
#define GPU_MEM_BASE GPU_UNCACHED_BASE

#define BUS_ADDRESS(addr)   (((addr) & ~0xC0000000) | GPU_MEM_BASE)

void* memcpy(void* dest, const void* src, unsigned int len);

#endif 


