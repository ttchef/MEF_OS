
#ifndef STRING_H
#define STRING_H 

#ifndef TYPES_H
#include "types.h"
#endif


u32 strlen(const char* string);

void itoa_dec(i32 value, char* buffer);
void itoa_hex(u32 value, char* buffer);
void itoa_bin(u32 value, char* buffer);
char* text_format(char* out, const char* string, ...);

#endif


