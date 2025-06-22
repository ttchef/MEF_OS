
#include "font.h"
#include "io.h"
#ifndef TYPES_H
#include "types.h"
#endif

#ifndef RAYCAST_H
#include "raycast.h"
#endif

#ifndef FRAMEBUFFER_H
#include "fb.h"
#endif

#ifndef INPUT_H
#include "input.h"
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

void rc_get_input() {
    char buffer[10];
    u32 k = uart_get_input(buffer, 10);
    
    if (input_check_key_pressed('a', buffer, k)) { px -= 6; }
    if (input_check_key_pressed('d', buffer, k)) { px += 6; }
    if (input_check_key_pressed('w', buffer, k)) { py -= 6; }
    if (input_check_key_pressed('s', buffer, k)) { py += 6; }

    
}

void rc_draw_player() {
    draw_rect(px, py, 8, 8,RGB_RED, CENTER);
}

void rc_display() {

    
    rc_get_input();

    rc_draw_player();


}

