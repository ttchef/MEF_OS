
#include "io.h"
#include "fb.h"
#include "utils.h"

void main()
{
    uart_init(&uart_init_v);

    uart_write_text("[DEBUG] Init Kernel!", UART_NEW_LINE);
    uart_write_text("[DEBUG] Init UART!", UART_NEW_LINE);

    frame_buffer_init();

    for (int y = 0; y < 1080; y++) {
        for (int x = 0; x < 1920; x++) {
            draw_pixel(x, y, (Color){20, 200, 5, 255});
        }
    }

    uart_write_text("[DEBUG] Kernel Loop!", UART_NEW_LINE);


    while(1);
}

