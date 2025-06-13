
#ifndef UTILS_H
#define UTILS_H

#ifndef TYPES_H
#include "types.h"
#endif

// Get Framebuffer Offset
u32 get_fb_of(u32 x, u32 y);

void draw_pixel_struct(u32 x, u32 y, Color color, u64 *buffer);
void draw_pixel_u32(u32 x, u32 y, u32 color, u64 *buffer);

void clear_color(Color color, u64* buffer);


#endif

