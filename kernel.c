
#include "globals.h"
#include "io.h"
#include "fb.h"
#include "timer.h" 
#include "dma.h"
#include "memory.h"

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
        draw_string("MEF OS", 30, 30, color, 10);
        draw_string("By Jens & Mef", 70 , 150, color, 5);

        /*
        draw_char('M', 0, 0, color, 4);
        draw_char('A', 40, 0, color, 4);
        draw_char('T', 80, 0, color, 4);
        draw_char('T', 120, 0, color, 4);
        draw_char('E', 160, 0, color, 4);
        draw_char('F', 200, 0, color, 4);
        */

        swap_buffers();

        uart_write_uint(stop_bench(), UART_NEW_LINE);

        wait_ms(100);

    }

    wait_s(5);
    uart_write_text("[DEBUG] Kernel Loop!", UART_NEW_LINE);

    while(1);
}

