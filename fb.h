
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#ifndef TYPES_H
#include "types.h"
#endif

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
unsigned long long* swap_buffers();

// Utils
u32 get_fb_of(u32 x, u32 y);
void draw_pixel_struct(u32 x, u32 y, Color color, u64 *buffer);
void draw_pixel_u32(u32 x, u32 y, u32 color, u64 *buffer);

void clear_color(Color color, u64* buffer);

// Helper functions
Vec2 get_virtual_offset();
Vec2 get_virtual_screen_dimensions();

void validate_framebuffer();
void test_virtual_screen_heights();

unsigned int check_mailbox_overall();
unsigned int parse_mailbox_message(u32 size);

unsigned int get_pixel_order();

#endif 

