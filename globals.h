
#ifndef GLOBALS_H
#define GLOBALS_H

#define PERIPHERAL_BASE 0xFE000000

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080
#define DEPTH 32

#define FRAMEBUFFER_SIZE 8355840/4

extern unsigned int* framebuffer;

extern unsigned int pitch;
extern unsigned int num_pixels;

#endif

