
#include "string.h"

u32 strlen(const char* string) {
    u32 i = 0;
    while(*string != '\0') {
        i++;
        string++;
    }
    return i;
}

