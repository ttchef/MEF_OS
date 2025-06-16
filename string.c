
#include "string.h"

#include <stdarg.h>

u32 strlen(const char* string) {
    u32 i = 0;
    while(*string != '\0') {
        i++;
        string++;
    }
    return i;
}

void itoa_dec(i32 value, char *buffer) {
    i32 i = 0;
    u8 negative = 0;
    char temp[12];

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    if (value < 0) {
        negative = 1;
        value *= -1;
    }

    while (value) {
        temp[i++] = '0' + (value % 10);
        value /= 10;
    }


    i32 j = 0;
    if (negative) {
        buffer[j++] = '-';   
    }

    while (i--) {
        buffer[j++] = temp[i];
    }
    buffer[j] = '\0';


}

void itoa_hex(u32 value, char *buffer) {
    const char* hex = "0123456789ABCDEF";
    char temp[9];
    i32 i = 0;

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = 'x';
        buffer[2] = '0';
        buffer[3] = '\0';
        return;
    } 

    while (value) {
        temp[i++] = hex[value & 0xF];
        value >>= 4;
    }

    i32 j = 0;
    buffer[j++] = '0';
    buffer[j++] = 'x';
    while (i--) {
        buffer[j++] = temp[i];
    }
    buffer[j] = '\0';
}

void itoa_bin(u32 value, char *buffer) {
    char temp[32];
    
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = 'b';
        buffer[2] = '0';
        buffer[3] = '\0';
        return;
    }

    u32 j = 0;
    i32 bit = 31;
    buffer[j++] = '0';
    buffer[j++] = 'b';

    while (bit >= 0 && ((value >> bit) & 1) == 0) {
        bit--;
    }

    for (; bit >= 0; bit--) {
        buffer[j++] = ((value >> bit) & 1) ? '1' : '0';
    }

    buffer[j] = '\0';

}

void text_format(char* out, const char* string, ...) {

    va_list vlist;
    va_start(vlist, string);

    char* buf = out;
    while (*string != '\0') {
        if (*string == '%') {
            string++;
            char temp[32];
            switch (*string) {
                case 's': {
                    char* str = va_arg(vlist, char*);
                    while (*str != '\0') *buf++ = *str++;
                    break;
                }
                case 'd': {
                    i32 num = va_arg(vlist, i32);
                    itoa_dec(num, temp);
                    char* t = temp;
                    while (*t != '\0') *buf++ = *t++;
                    break;
                }
                case 'x': {
                    u32 num = va_arg(vlist, u32);
                    itoa_hex(num, temp);
                    char* t = temp;
                    while (*t != '\0') *buf++ = *t++;
                    break;
                }
                case 'b': {
                    u32 num = va_arg(vlist, u32);
                    itoa_bin(num, temp);
                    char* t = temp;
                    while (*t != '\0') *buf++ = *t++;
                    break;
                }
                case '%': {
                    *buf++ = '%';
                    break;
                }
                default:
                    *buf++ = '?';
            }
        }
        else {
            *buf++ = *string;
        }
        string++;
    }

    *buf = '\0';

    va_end(vlist);
}

