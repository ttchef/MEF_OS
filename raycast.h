
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
    #define GRIDSIZE 8
#else 
    #define GRIDSIZE 4
#endif

#define MAP_WIDTH 24 
#define MAP_HEIGHT 24 
#define MAP_SIZE (MAP_WIDTH * MAP_HEIGHT)

extern double posX, posY; // player pos 
extern double dirX, dirY; // looking direction
extern double planeX, planeY; // camera position

extern u32 map[MAP_SIZE];

void rc_init();
void rc_display();
void rc_get_input(double moveSpeed, double rotSpeed);
void rc_draw_map_2D();


#endif


