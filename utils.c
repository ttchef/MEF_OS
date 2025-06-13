
#include "utils.h"
#include "globals.h"
#include "fb.h"
#include "io.h"

#define CONVERT_COLOR_STRUCT(color) \
    ((color.a << 24) | (color.r << 16) | (color.g << 8) | color.b)


u32 get_fb_of(u32 x, u32 y) {
    return (y * pitch / 4) + x;
}

void draw_pixel_struct(u32 x, u32 y, Color color, u64 *buffer) {
    buffer[(y*pitch/4)+x] = CONVERT_COLOR_STRUCT(color); 
}

void draw_pixel_u32(u32 x, u32 y, u32 color, u64* buffer) {
    buffer[(y*pitch/4)+x] = color;
}


/*
Time Spent debugging double buffering with virtual offset:
- 3 Day 
- 15 Hours
*/
void clear_color(Color color, u64 *buffer) {

    u64* ptr = buffer;
    u64* end = ptr + (fb_size/16);
    u32 color32 = CONVERT_COLOR_STRUCT(color);
    u64 color64 = ((u64)color32 <<  32) | color32;

    while (ptr + 4 <= end) {

        ptr[0] = color64;
        ptr[1] = color64;
        ptr[2] = color64;
        ptr[3] = color64;
        ptr += 4;
    }

    while (ptr < end) {
        *ptr++ = color64;
    }

}


