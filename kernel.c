
#include "io.h"
#include "fb.h"
#include "utils.h"
#include "timer.h" 
#include "dma.h"

void main()
{
    uart_init(&uart_init_v);

    uart_write_text("[DEBUG] Init Kernel!", UART_NEW_LINE);
    uart_write_text("[DEBUG] Init UART!", UART_NEW_LINE);

    frame_buffer_init();

    u16 r = 0;
    u16 g = 100;
    u16 b = 200;
    u16 inc = 10;

    // Test array 
    volatile u32* array = (volatile u32*)0x04000000CULL;
    u32 heap_size = 1000000;
    array[heap_size/2] = 20;


    while (1) {
        
        start_bench();

        r+=inc;
        g+=inc;
        b+=inc;

        clear_color_u32(make_color(r, g, b));
        uart_write_uint((u32)stop_bench(), UART_NEW_LINE);

    }

    wait_s(5);
    uart_write_text("[DEBUG] Kernel Loop!", UART_NEW_LINE);


    while(1);
}

