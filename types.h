
#ifndef TYPES_H
#define TYPES_H

#ifndef FONT_H
#include "font.h"
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

#define RGB_RED (Color){255,0,0};
#define RGB_GREEN (Color){0,255,0};
#define RGB_BLUE (Color){0,0,255};

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

typedef struct {
    u32 x;
    u32 y;
} Vec2;

typedef struct {
    u32 x;
    u32 y;
    u32 z;
} Vec3;

typedef struct {
    char* string;
    Vec2 pos;
    u32 scale;
    Color color;
    enum FONT_ORIENT orientation;
} Text;



#endif

