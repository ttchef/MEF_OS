
#include "globals.h"
#include "io.h"
#include "fb.h"
#include "utils.h"
#include "timer.h" 
#include "dma.h"
#include "memory.h"

void main()
{
    uart_init(&uart_init_v);
    framebuffer_init();

    u16 r = 100;
    u16 g = 0;
    u16 b = 0;
    u16 inc = 1;

    while (1) {
        
        start_bench();

        r+=inc;
    
        u64* buffer = swap_buffers();
        clear_color_u32(make_color(r, g, b), buffer);
        

       
        uart_write_uint(stop_bench(), UART_NEW_LINE);

    }

    wait_s(5);
    uart_write_text("[DEBUG] Kernel Loop!", UART_NEW_LINE);


    while(1);
}

