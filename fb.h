
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#ifndef TYPES_H
#include "types.h"
#endif

#ifndef FONT_H
#include "font.h"
#endif

#ifndef GLOBALS_H
#include "globals.h"
#endif

#define CONVERT_COLOR_STRUCT(color) \
    ((color.a << 24) | (color.r << 16) | (color.g << 8) | color.b)


enum {
    FB_PIXEL_ORDER_BGR = 0x0,
    FB_PIXEL_ORDER_RGB = 0x1
};

extern volatile unsigned int __attribute__((aligned(16))) mbox[35];

extern unsigned long long *fb_buffer1;
extern unsigned long long *fb_buffer2;
extern unsigned int fb_size;
extern unsigned int pitch;
extern unsigned int num_pixels;

extern u64 *active_buffer;
extern unsigned int buffer_one_active;

void framebuffer_init();
void set_virtual_offset(unsigned int x, unsigned int y);
void swap_buffers();

// Utils
u32 get_fb_of(u32 x, u32 y);
//void draw_pixel(u32 x, u32 y, Color color);
void draw_rect(u32 x, u32 y, u32 width, u32 height, Color color, enum FONT_ORIENT orientation);
void draw_line(i32 x1, i32 y1, i32 x2, i32 y2, Color color);

void draw_text(Text text);
void draw_string(char* string, u32 x, u32 y, Color color, u32 scale);
void draw_char(char c, u32 x, u32 y, Color color, u32 scale);
void clear_color(Color color);

// Helper functions
Vec2 get_virtual_offset();
Vec2 get_virtual_screen_dimensions();

void validate_framebuffer();
void test_virtual_screen_heights();

unsigned int check_mailbox_overall();
unsigned int parse_mailbox_message(u32 size);

unsigned int get_pixel_order();

static inline void draw_pixel(u32 x, u32 y, Color color) {
 
    if (x < 0 || x > SCREENWIDTH-1 || y < 0 || y > SCREENHEIGHT-1) return;

    ((u32*)active_buffer)[(y*SCREENWIDTH)+x] = CONVERT_COLOR_STRUCT(color);
    
}

#endif 

