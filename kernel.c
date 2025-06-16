
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
    volatile u32 posx = 800;

    while (1) {
        
        //start_bench();

        r+=inc;
        g+=inc;
        b+=inc;

        clear_color((Color){35, 55, 187});

        Color color = {200, 25, 55};
        Text text = {"Schroch", (Vec2){posx++,SCREENHEIGHT/2}, 10, color, CENTER};
        draw_text(text);
    
        char buffer[100] __attribute__((aligned(16)));
        u32 i = uart_get_input(buffer, sizeof(buffer));
        uart_print_receive(buffer, i);

        
        swap_buffers();

        wait_ms(16);

        //uart_write_uint(stop_bench(), UART_NEW_LINE);


    }

    wait_s(5);
    uart_write_text("[DEBUG] Kernel Loop!", UART_NEW_LINE);

    while(1);
}

