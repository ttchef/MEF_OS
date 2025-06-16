
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
        
        start_bench();

        r+=inc;
        g+=inc;
        b+=inc;

        clear_color((Color){35, 55, 187});

        Color color = {200, 25, 55};
        Text text = {"Schroch", (Vec2){posx++,SCREENHEIGHT/2}, 10, color, CENTER};
        draw_text(text);
    
        
        
        char buffer1[100] __attribute__((aligned(16)));
        text_format(buffer1, "Yoo epic test number in decimal: %d\n", 5);
        uart_write_text(buffer1, UART_NONE);
        
        
        char buffer2[100];
        text_format(buffer2, "Yoo epic test number in hex: %x\n", 5);
        uart_write_text(buffer2, UART_NONE);

        char buffer3[100];
        text_format(buffer3, "Yoo epic test number in binary: %b\n", 5);
        uart_write_text(buffer3, UART_NONE);

        
        char buffer4[100];
        text_format(buffer4, "Yoo epic character test: %s\n", "A");
        uart_write_text(buffer4, UART_NONE);

        char buffer5[100];
        text_format(buffer5, "Yoo epic percent test: %%\n"); // functions
        uart_write_text(buffer5, UART_NONE);



        swap_buffers();

        uart_write_uint(stop_bench(), UART_NEW_LINE);

        wait_ms(100);

    }

    wait_s(5);
    uart_write_text("[DEBUG] Kernel Loop!", UART_NEW_LINE);

    while(1);
}

