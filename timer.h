
#ifndef TIMER_H
#define TIMER_H

#ifndef TYPES_H
#include "types.h"
#endif

enum {
    TIMER_BASE = 0xFE003000,
    TIMER_CLO = TIMER_BASE + 0x04,
    TIMER_CHI = TIMER_BASE + 0x08,
};

unsigned long long get_system_timer();

void wait_ms(unsigned long long n);
void wait_s(unsigned long long n);

void start_bench();
unsigned long long stop_bench();
unsigned long long stop_bench_s();

#endif

