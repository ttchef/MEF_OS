
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

    float LOW_LIMIT = 0.0167f;
    float HIGH_LIMIT = 0.1f;
    
    u64 lastTime = get_system_timer();

    while (1) {

        start_bench();

        clear_color(RGB_BLACK);

        u64 currentTime = get_system_timer();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        if ( deltaTime < LOW_LIMIT )
            deltaTime = LOW_LIMIT;
        else if ( deltaTime > HIGH_LIMIT )
            deltaTime = HIGH_LIMIT;

        lastTime = currentTime;

        rc_display();
        rc_draw_map_2D();
        rc_get_input(deltaTime * 5.0, deltaTime * 3.0);



        //wait_ms(55);
        swap_buffers();

        printf("[DEBUG] Time for hole frame: %d\n", stop_bench());




    }

    uart_write_text("[WARNING] Kernel Hold Loop!", UART_NEW_LINE);

    while(1);
}

