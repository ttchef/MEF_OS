
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H


extern volatile unsigned int __attribute__((aligned(16))) mbox[30];

void frame_buffer_init();
unsigned int check_mailbox_response();

#endif 

