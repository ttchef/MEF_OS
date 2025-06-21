
#ifndef RAYCAST_H
#define RAYCAST_H

#ifndef TYPES_H
#include "types.h"
#endif 

#ifndef GLOBALS_H
#include "globals.h"
#endif

extern float px,py; // player pos

extern const u32 mapX;
extern const u32 mapY;
extern const u32 mapSize;

extern u32 map[];

void rc_init();
void rc_display();
void rc_draw_player();

#endif


