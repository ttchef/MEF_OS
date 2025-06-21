
#ifndef RAYCAST_H
#include "raycast.h"
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

void rc_init() {

    px = 300.0f;
    py = 300.0f;

}

void rc_draw_player() {
    
}

void rc_display() {
    

}

