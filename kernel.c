
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
        draw_char('M', 0, 0, color);
        draw_char('A', 10, 0, color);
        draw_char('T', 20, 0, color);
        draw_char('T', 30, 0, color);
        draw_char('E', 40, 0, color);
        draw_char('F', 50, 0, color);

        swap_buffers();

        uart_write_uint(stop_bench(), UART_NEW_LINE);

    }

    wait_s(5);
    uart_write_text("[DEBUG] Kernel Loop!", UART_NEW_LINE);

    while(1);
}

