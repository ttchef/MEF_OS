
#include "font.h"
#include "globals.h"
#include "io.h"
#include "fb.h"
#include "timer.h" 
#include "dma.h"
#include "memory.h"
#include "types.h"
#include "string.h"

void main()
{
    uart_init(&uart_init_v);
    framebuffer_init();

    u16 r = 100;
    u16 g = 200;
    u16 b = 150;
    u16 inc = 1;

    while (1) {
        
        start_bench();

        r+=inc;
        g+=inc;
        b+=inc;

        clear_color((Color){35, 55, 187});

        Color color = {200, 25, 55};
        Text text = (Text){"Schroch", (Vec2){SCREENWIDTH/2,SCREENHEIGHT/2}, 10, color, CENTER};
        draw_text(text);

        //draw_string("MEF OS", 30, 30, color, 10);
        //draw_string("By Jens & Mef", SCREENWIDTH/2 , SCREENHEIGHT/2, color, 5);

        swap_buffers();

        uart_write_uint(stop_bench(), UART_NEW_LINE);

        wait_ms(100);

    }

    wait_s(5);
    uart_write_text("[DEBUG] Kernel Loop!", UART_NEW_LINE);

    while(1);
}

