
#include "memory.h"
#include "utils.h"

void* memcpy(void* dest, const void* src, u32 len) {
    u32* d = (u32*)dest;
    const u32* s = (const u32*)src;
    u32 count = len/4;

    while (count--) {
        *d++ = *s++;
    }
    return dest;
}



