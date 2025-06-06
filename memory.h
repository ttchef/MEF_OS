
#ifndef MEMORY_H
#define MEMORY_H 

void* memcpy(void* dest, const void* src, unsigned int len);

#define GPU_CACHED_BASE 0x40000000
#define GPU_UNCACHED_BASE 0xC0000000
#define GPU_MEM_BASE GPU_UNCACHED_BASE

#define BUS_ADDRESS(addr)   (((addr) & ~0xC0000000) | GPU_MEM_BASE)

#endif 


