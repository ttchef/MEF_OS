
#ifndef RAYCAST_H
#define RAYCAST_H

#ifndef TYPES_H
#include "types.h"
#endif 

#ifndef GLOBALS_H
#include "globals.h"
#endif

float px,py; // player pos

const u32 mapX = 8;
const u32 mapY = 8;
const u32 mapSize = mapX * mapY;

u32 map[] = {
    1,1,1,1,1,1,1,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,
};

void rc_init();
void rc_display();
void rc_draw_player();

#endif


