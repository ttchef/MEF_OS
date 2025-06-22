
#ifndef MATH_H
#define MATH_H 

#ifndef TYPES_H
#include "types.h"
#endif

extern const double PI;
extern const u8 sine_table[91];

float isin(i16 i);
float icos(i16 i);

static inline float math_convert_degree_to_radians(float degrees) {
    return degrees * (PI / 180.0f);
}

static inline float math_convert_radians_to_degree(float radians) {
    return radians * 180.0f / PI;
}

static inline u32 abs(u32 n) {
    if (n < 0) {
        return -n;
    }
    return n;
} 

static inline u32 fabs(double n) {
    if (n < 0) {
        return -n;
    }
    return n;
} 

#endif

