
#ifndef UTILS_H
#define UTILS_H

#ifndef TYPES_H
#include "types.h" 
#endif 

// get Exception Level
static inline u32 get_current_el() {
    u32 el_reg;
    asm volatile ("mrs %0, CurrentEL" : "=r"(el_reg));
    // only bit 2-3 we care about
    return (el_reg >> 2) & 0x3;
}

static inline Color color_div_by_factor(Color color, u32 factor) {
    Color c = color;
    c.r /= factor;
    c.g /= factor;
    c.b /= factor;
    c.a /= factor;
    return c;
}


#endif

