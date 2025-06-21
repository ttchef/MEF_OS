
#include "input.h"
#include "io.h"

u32 input_check_key_pressed(u32 key) {
    char buffer[10];
    u32 k = uart_get_input(buffer, 10);

    for (u32 i = 0; i < k; i++) {
        if ((u8)buffer[i] == key) {
            return 1;
        }
    }
    return 0;
}



