
// types
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef short i16;
typedef int i32;
typedef long long i64;

typedef struct {
    u16 r;
    u16 b;
    u16 g;
    u16 a;
} Color;

// Color
u32 make_color(u32 red, u32 green, u32 blue);
u32 make_color_a(u32 red, u32 green, u32 blue, u32 alpha);

u32 make_color_struct(Color color);

// Get Framebuffer Offset
u32 get_fb_of(u32 x, u32 y);

void draw_pixel(u32 x, u32 y, Color color);
void draw_pixel_u32(u32 x, u32 y, u32 color);

void clear_color(Color color);
void clear_color_u32(u32 color);

