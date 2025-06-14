
#ifndef FONT_H
#define FONT_H 

#define FONT_WIDTH 8
#define FONT_HEIGHT 8

enum FONT_ORIENT {
    CENTER = 0,
    TOP_LEFT = 1
};

extern char font_buffer[128][8];

#endif
