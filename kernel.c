
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

    while (1) {

        start_bench();
        rc_display();
        double frame_time = stop_bench();
        rc_get_input(5.0+3.0, 3.0+3.0);



        //wait_ms(55);
        swap_buffers();

        printf("[DEBUG] Time for hole frame: %d\n", stop_bench());




    }

    uart_write_text("[WARNING] Kernel Hold Loop!", UART_NEW_LINE);

    while(1);
}

