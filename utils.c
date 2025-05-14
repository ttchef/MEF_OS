
#include "utils.h"
#include "globals.h"

u32 make_color(u32 red, u32 green, u32 blue) {
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

    u32 i;
    for (; i+3 < num_pixels; i+=4) {
        framebuffer[i] = color_u32;
        framebuffer[i+1] = color_u32;
        framebuffer[i+2] = color_u32;
        framebuffer[i+3] = color_u32;
    }

    for (; i < num_pixels;i++) {
        framebuffer[i] = color_u32;
    }

}

void clear_color_u32(u32 color) {

    u32 i;
    for (; i+3 < num_pixels; i+=4) {
        framebuffer[i] = color;
        framebuffer[i+1] = color;
        framebuffer[i+2] = color;
        framebuffer[i+3] = color;
    }

    for (; i < num_pixels;i++) {
        framebuffer[i] = color;
    }


}

