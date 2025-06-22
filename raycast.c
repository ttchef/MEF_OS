
#include "font.h"
#include "io.h"
#include "math.h"
#include "types.h"
#include "raycast.h"
#include "fb.h"
#include "input.h"

float px,py; // player pos
float pdx,pdy,pa;

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

    float pa_d = math_convert_radians_to_degree(pa); 
    pdx = icos(pa_d) * 5; pdy = isin(pa_d) * 5;
}

void rc_get_input() {
    char buffer[10];
    u32 k = uart_get_input(buffer, 10);
    
    if (input_check_key_pressed('a', buffer, k)) { 
        pa -= 0.1;
        if (pa < 0) {
            pa += 2 * PI;
        } 

        float pa_d = math_convert_radians_to_degree(pa); 
        pdx = icos(pa_d) * 5;
        pdy = isin(pa_d) * 5; 
    }

    if (input_check_key_pressed('d', buffer, k)) {
        pa += 0.1;
        if (pa > 2*PI) {
            pa -= 2 * PI;
        } 

        float pa_d = math_convert_radians_to_degree(pa); 
        pdx = icos(pa_d) * 5;
        pdy = isin(pa_d) * 5; 
    }
    if (input_check_key_pressed('w', buffer, k)) { px += pdx; py += pdy; }
    if (input_check_key_pressed('s', buffer, k)) { px -= pdx; py -= pdy; }
    
}

void rc_draw_player() {
    draw_rect(px, py, 8, 8,RGB_RED, CENTER);

    i32 x1 = (i32)(px + pdx * 5);
    i32 y1 = (i32)(py + pdy * 5);
    draw_line(px, py, x1, y1, RGB_YELLOW);
}

void rc_draw_map_2D() {
    for (u32 y = 0; y < mapY; y++) {
        for (u32 x = 0; x < mapX; x++) {
            Color color;
            (map[y*mapX+x] == 1) ? (color = RGB_WHITE) : (color = RGB_BLACK);
            draw_rect(x * GRIDSIZE, y * GRIDSIZE, GRIDSIZE-1, GRIDSIZE-1, color, TOP_LEFT);
        }
    }
}

void rc_display() {

    
    rc_get_input();
    //rc_draw_map_2D();
    rc_draw_player();


}

