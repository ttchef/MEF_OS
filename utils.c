
#include "utils.h"
#include "globals.h"
#include "fb.h"

u32 make_color(u8 red, u8 green, u8 blue) {
    return (0xFF << 24) | (red << 16) | (green << 8) | blue;
}

u32 make_color_a(u32 red, u32 green, u32 blue, u32 alpha) {
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

u32 make_color_struct(Color color) {
    return (color.a << 24) | (color.r << 16) | (color.g << 8) | color.b;
}


u32 get_fb_of(u32 x, u32 y) {
    return (y * pitch / 4) + x;
}

void draw_pixel(u32 x, u32 y, Color color) {
    framebuffer[(y*pitch/4)+x] = make_color_struct(color); 
}

void draw_pixel_u32(u32 x, u32 y, u32 color) {
    framebuffer[(y*pitch/4)+x] = color;
}

void clear_color(Color color) {
    u32 color_u32 = make_color_struct(color);

    u32* ptr = fb_buffer1;
    u32* end = ptr + num_pixels;
    
    while (ptr + 3 < end) {
        ptr[0] = color_u32;
        ptr[1] = color_u32; 
        ptr[2] = color_u32; 
        ptr[3] = color_u32; 
        ptr += 4;
    }

    while (ptr < end) {
        *ptr++ = color_u32;
    }

}

void clear_color_u32(u32 color) {
    u32* ptr = fb_buffer1;
    u32* end = ptr + num_pixels;
    
    while (ptr + 3 < end) {
        ptr[0] = color;
        ptr[1] = color; 
        ptr[2] = color; 
        ptr[3] = color; 
        ptr += 4;
    }

    while (ptr < end) {
        *ptr++ = color;
    }
}

u16 make_color_16bit(u32 r, u32 g, u32 b) {
    return (r << 11) | (g << 5) | b;
}

void clear_color_16bit(u16 color) {
    u16* ptr = (u16*)framebuffer;
    u16* end = ptr + num_pixels;
    
    while (ptr + 3 < end) {
        ptr[0] = color;
        ptr[1] = color; 
        ptr[2] = color; 
        ptr[3] = color; 
        ptr += 4;
    }

    while (ptr < end) {
        *ptr++ = color;
    }

}

