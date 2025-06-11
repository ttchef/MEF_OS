
#include "utils.h"
#include "globals.h"
#include "fb.h"
#include "io.h"

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

    u64* ptr = fb_buffer1;
    u64* end = ptr + num_pixels - 4;
    
    while (ptr < end) {
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

/*
Time Spent debugging double buffering with virtual offset:
- 3 Day 
- 15 Hours
*/
void clear_color_u32(u32 color, u64* buffer) {

    //uart_write_text("\n\n[DEBUG] Beginn clear color drawing!\n", UART_NONE);

    u64* ptr = buffer;
    u64* end = ptr + (fb_size/16);

    /*
    uart_write_text("[DEBUG] buffer: ", UART_NONE);
    uart_write_uint((u64)ptr, UART_NEW_LINE);
    uart_write_text("[DEBUG] num_pixels: ", UART_NONE);
    uart_write_uint(num_pixels, UART_NEW_LINE);
    uart_write_text("[DEBUG] end: ", UART_NONE);
    uart_write_uint((u64)end, UART_NEW_LINE);
    */

    u64 color64 = ((u64)color <<  32) | color;

    while (ptr + 4 <= end) {

        /*
        if ((u64)ptr % 10000 == 0) {
            uart_write_text("\n[DEBUG] ptr: ", UART_NONE);
            uart_write_uint((u64)ptr, UART_NEW_LINE);
        }
        */


        ptr[0] = color64;
        ptr[1] = color64;
        ptr[2] = color64;
        ptr[3] = color64;
        ptr += 4;
    }

    //uart_write_text("\n[DEBUG] Finsihed big thing!\n”", UART_NONE);

    while (ptr < end) {
        *ptr++ = color64;
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

