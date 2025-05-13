

#include "timer.h" 
#include "utils.h"

// no mmio_read because of performance
u64 get_system_timer() {
    u32 low, high;
    low = *(volatile u32*)TIMER_CLO; 
    high = *(volatile u32*)TIMER_CHI;

    return (high << 32) | low;
}

void wait_ms(u64 n) {
    // convert micro to milli 
    n *= 1000;
    u64 last_time = get_system_timer();
    while(get_system_timer() - last_time < n);
}

void wait_s(u64 n) {
    // convert micro to sec
    n *= 1000000;
    u64 last_time = get_system_timer();
    while(get_system_timer() - last_time < n);
}

