
#include "utils.h"
#include "fb.h"

u32 make_color(u32 red, u32 green, u32 blue) {
    return (0xFF << 24) | (red << 16) | (green << 8) | blue;
}

u32 make_color_a(u32 red, u32 green, u32 blue, u32 alpha) {
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

u32 make_color_struct(Color color) {
    return (color.a << 24) | (color.a << 16) | (color.g << 8) | color.b;
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

