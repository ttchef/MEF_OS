
#ifndef RAYCAST_H
#define RAYCAST_H

#ifndef TYPES_H
#include "types.h"
#endif 

#ifndef MATH_H
#include "math.h"
#endif

#ifndef GLOBALS_H
#include "globals.h"
#endif

#ifdef ULTRA_HD
    #define GRIDSIZE 240
#else 
    #define GRIDSIZE 80
#endif


extern float px,py; // player pos
extern float pdx,pdy,pa;

extern const u32 mapX;
extern const u32 mapY;
extern const u32 mapSize;

extern u32 map[];

void rc_init();
void rc_display();
void rc_get_input();

void rc_draw_player();
void rc_draw_map_2D();


#endif


