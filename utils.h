
#ifndef UTILS_H
#define UTILS_H

// types
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

typedef struct {
    u8 r;
    u8 b;
    u8 g;
    u8 a;
} Color;

typedef struct {
    u32 x;
    u32 y;
} Vec2;

typedef struct {
    u32 x;
    u32 y;
    u32 z;
} Vec3;


// Color
u32 make_color(u8 red, u8 green, u8 blue);
u32 make_color_a(u32 red, u32 green, u32 blue, u32 alpha);

u32 make_color_struct(Color color);

// Get Framebuffer Offset
u32 get_fb_of(u32 x, u32 y);

void draw_pixel(u32 x, u32 y, Color color);
void draw_pixel_u32(u32 x, u32 y, u32 color);

void clear_color(Color color);
void clear_color_u32(u32 color, u64* buffer);

void clear_color_16bit(u16 color);
u16 make_color_16bit(u32 r, u32 g, u32 b);

#endif
