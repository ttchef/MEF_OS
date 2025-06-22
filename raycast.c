
#include "font.h"
#include "globals.h"
#include "io.h"
#include "math.h"
#include "types.h"
#include "raycast.h"
#include "fb.h"
#include "input.h"
#include "utils.h"

double posX, posY, dirX, dirY, planeX, planeY;

u32 map[] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1,
    1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1,
    1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

void rc_init() {
    posX = 22;
    posY = 12;
    dirX = -1;
    dirY = 0;
    planeX = 0;
    planeY = 0.66;

}

void rc_get_input(double moveSpeed, double rotSpeed) {
    
    char buffer[10];
    u32 k = uart_get_input(buffer, 10);
    
    if (input_check_key_pressed('w', buffer, k)) {
        if (map[(i32)(posY * MAP_WIDTH + (i32)(posX + dirX * moveSpeed))] == 0) posX += dirX * moveSpeed;
        if (map[(i32)((posY + dirY * moveSpeed) * MAP_WIDTH + posX)] == 0) posY += dirY * moveSpeed;
    }

    else if (input_check_key_pressed('s', buffer, k)) {
        if (map[(i32)(posY * MAP_WIDTH + (i32)(posX - dirX * moveSpeed))] == 0) posX -= dirX * moveSpeed;
        if (map[(i32)((posY - dirY * moveSpeed) * MAP_WIDTH + posX)] == 0) posY -= dirY * moveSpeed;
    }


    if (input_check_key_pressed('d', buffer, k)) {
        float rot_speed_r = math_convert_radians_to_degree(rotSpeed);

        double oldDirX = dirX;
        dirX = dirX * icos(-rot_speed_r) - dirY * isin(-rot_speed_r);
        dirY = oldDirX * isin(-rot_speed_r) + dirY * icos(-rot_speed_r);

        double oldPlaneX = planeX;
        planeX = planeX * icos(-rot_speed_r) - planeY * isin(-rot_speed_r);
        planeY = oldPlaneX * isin(-rot_speed_r) + planeY * icos(-rot_speed_r);
    }

    if (input_check_key_pressed('a', buffer, k)) {
        float rot_speed_r = math_convert_radians_to_degree(rotSpeed);

        double oldDirX = dirX;
        dirX = dirX * icos(rot_speed_r) - dirY * isin(rot_speed_r);
        dirY = oldDirX * isin(rot_speed_r) + dirY * icos(rot_speed_r);

        double oldPlaneX = planeX;
        planeX = planeX * icos(rot_speed_r) - planeY * isin(rot_speed_r);
        planeY = oldPlaneX * isin(rot_speed_r) + planeY * icos(rot_speed_r);
    }


}


void rc_display() {
    
    for (i32 x = 0; x < SCREENWIDTH; x++) {
        double cameraX = 2 * x / (double)SCREENWIDTH - 1; // Get Coords in Camera View
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        // box of the map we are in
        u32 mapX = (u32)posX;
        u32 mapY = (u32)posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        i32 stepX;
        i32 stepY;
        i32 hit = 0;
        i32 side;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        // perform DDA 
        while (hit == 0) {
            // jump to x
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            // jump to y
            else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (map[mapY*MAP_WIDTH+mapX] > 0) hit = 1;
        }

        double perpWallDist;
        if (side == 0) perpWallDist = (sideDistX - deltaDistX);
        else perpWallDist = (sideDistY - deltaDistY);

        i32 lineHeight = (int)(SCREENHEIGHT / perpWallDist);

        int drawStart = -lineHeight / 2 + SCREENHEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        i32 drawEnd = lineHeight / 2 + SCREENHEIGHT / 2;
        if (drawEnd >= SCREENHEIGHT) drawEnd = SCREENHEIGHT - 1;
        
        // color of the block
        Color color;
        switch (map[mapY * MAP_WIDTH + mapX]) {
            case 1: color = RGB_RED; break;
            case 2: color = RGB_GREEN; break;
            case 3: color = RGB_BLUE; break;
            case 4: color = RGB_WHITE; break;
            default: color = RGB_YELLOW; break;
        }

        // brightness depeding on the side
        if (side == 1) { color = color_div_by_factor(color, 2); }
        draw_vertical_line(x, drawStart, drawEnd, color);
    }

}

