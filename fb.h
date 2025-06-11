
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "utils.h"

extern volatile unsigned int __attribute__((aligned(16))) mbox[35];

extern unsigned long long *fb_buffer1;
extern unsigned long long *fb_buffer2;
extern unsigned int fb_size;

void frame_buffer_init();
void set_virtual_offset(unsigned int x, unsigned int y);

// DEBUG 
Vec2 get_virtual_offset();
Vec2 get_virtual_screen_dimensions();

void validate_framebuffer();
void test_virtual_screen_heights();

unsigned int check_mailbox_overall();
unsigned int parse_mailbox_message(u32 size);

// ---

#endif 

