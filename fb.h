
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

extern volatile unsigned int __attribute__((aligned(16))) mbox[30];

extern unsigned int* fb_buffer1;
extern unsigned int* fb_buffer2;
extern unsigned int fb_size;

void frame_buffer_init();
unsigned int check_mailbox_response();

#endif 

