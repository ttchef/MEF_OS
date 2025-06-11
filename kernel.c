
#include "globals.h"
#include "io.h"
#include "fb.h"
#include "utils.h"
#include "timer.h" 
#include "dma.h"
#include "memory.h"

u32 buffer_one_active = 1;

void main()
{
    /*
    extern char __kernel_start;
    uart_write_text("[DEBUG] Kernel Start: ", UART_NONE);
    uart_write_uint((u64)&__kernel_start, UART_NEW_LINE);
    */

    uart_init(&uart_init_v);

    uart_write_text("[DEBUG] Init Kernel!", UART_NEW_LINE);
    uart_write_text("[DEBUG] Init UART!", UART_NEW_LINE);

    frame_buffer_init();

    u16 r = 0;
    u16 g = 100;
    u16 b = 200;
    u16 inc = 10;


    while (1) {
        
        //start_bench();

        r+=inc;
        g+=inc;
        b+=inc;
    
        u32 virtual_screen_height = get_virtual_screen_dimensions().y;
        uart_write_text("[DEBUG] Vitrual Screenheight: ", UART_NONE);
        uart_write_uint(virtual_screen_height, UART_NEW_LINE);

        //set_virtual_offset(0, 0);

        /*
        Vec2 vir_offset = get_virtual_offset();
        uart_write_text("[DEBUG] Virtual Offset ", UART_NONE);
        uart_write_uint(vir_offset.x, UART_NONE);
        uart_write_text(" | ", UART_NONE);
        uart_write_uint(vir_offset.y, UART_NEW_LINE);
     
        uart_write_text("Wait 5s\n", UART_NONE);
        wait_s(5);
        uart_write_text("5 Secs done\n", UART_NONE);
        */

        if (buffer_one_active == 1) {
            clear_color_u32(make_color(r, g, b), fb_buffer1);
            set_virtual_offset(0, 0);
            buffer_one_active = 0;
            uart_write_text("[DEBUG] Buffer 1\n", UART_NONE);
        } else {
            clear_color_u32(make_color(r, g, b), fb_buffer2);
            set_virtual_offset(0, SCREENHEIGHT);
            buffer_one_active = 1;
            uart_write_text("[DEBUG] Buffer 2\n", UART_NONE);
        }


        /*
        for (int y = 0; y < SCREENHEIGHT; y++) {
            for (int x = 0; x < SCREENWIDTH; x++) {
                framebuffer[y * (pitch / 4) + x] = 0xFFFFFFFF; // Rot (BGR in Little Endian)
            }
            uart_write_text("Wrote one vertical line!\n", UART_NONE);
        }
*/

        /*
        if (buffer_one_active) {
            clear_color_u32(make_color(r, g, b), fb_buffer1);
            set_virtual_offset(0,SCREENHEIGHT);
            buffer_one_active = 0;
        } else {
            clear_color_u32(make_color(r, g, b), fb_buffer2);
            set_virtual_offset(0,0);
            buffer_one_active = 1;
        }
        */

        //uart_write_uint((u32)stop_bench(), UART_NEW_LINE);

    }

    wait_s(5);
    uart_write_text("[DEBUG] Kernel Loop!", UART_NEW_LINE);


    while(1);
}

