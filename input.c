
#ifndef INPUT_H 
#include "input.h"
#endif 

#ifndef IO_H
#include "io.h"
#endif

u32 input_check_key_pressed(char key, char *buffer, u32 size) {
    for (u32 i = 0; i < size; i++) {
        if ((u8)buffer[i] == key) {
            return 1;
        }
    }
    return 0;
}



