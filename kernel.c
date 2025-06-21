
#include "font.h"
#include "globals.h"
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
        
        rc_display();

        swap_buffers();

    }

    uart_write_text("[WARNING] Kernel Hold Loop!", UART_NEW_LINE);

    while(1);
}

