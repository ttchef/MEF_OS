
#include "globals.h"
#include "font.h"
#include "io.h"
#include "fb.h"
#include "timer.h" 
#include "dma.h"
#include "memory.h"
#include "types.h"
#include "string.h"
#include "utils.h"

#ifndef RAYCAST_H
#include "raycast.h"
#endif

void main()
{
    uart_init(&uart_init_v);
    framebuffer_init();
    rc_init();

    rc_draw_map_2D();
    swap_buffers();
    rc_draw_map_2D();

    while (1) {
        
        //start_bench();

        rc_display();

        //u64 time = stop_bench_us();
        //printf("Time For Player: %d\n", time);

        //start_bench();

        //wait_ms(55);
        swap_buffers();

       // time = stop_bench_us();
        //printf("Time For Swapping Buffers: %d\n", time);


    }

    uart_write_text("[WARNING] Kernel Hold Loop!", UART_NEW_LINE);

    while(1);
}

