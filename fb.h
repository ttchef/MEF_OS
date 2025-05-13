

extern volatile unsigned int __attribute__((aligned(16))) mbox[30];
extern unsigned int* framebuffer;
extern unsigned int pitch;

void frame_buffer_init();
unsigned int check_mailbox_response();

