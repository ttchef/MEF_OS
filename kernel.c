
#include "io.h"
#include "fb.h"
#include "utils.h"
#include "timer.h"

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

    while (1) {
        r+=inc;
        g+=inc;
        b+=inc;

        for (int y = 0; y < 1080; y++) {
            for (int x = 0; x < 1920; x++) {
                draw_pixel(x, y, (Color){r, g, b, 255});
            }
        }
        wait_ms(5);
        uart_write_text("Loop", UART_NEW_LINE);
    }


    uart_write_text("[DEBUG] Kernel Loop!", UART_NEW_LINE);


    while(1);
}

