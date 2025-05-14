

#include "timer.h" 
#include "utils.h"

u64 bench_current_time;
u64 bench_last_time;

// no mmio_read because of performance
u64 get_system_timer() {
    u32 low, high;
    low = *(volatile u32*)TIMER_CLO; 
    high = *(volatile u32*)TIMER_CHI;

    return ((u64)high << 32) | low;
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

void start_bench() {
    bench_last_time = get_system_timer();
}

u64 stop_bench() {
    bench_current_time = get_system_timer();
    return (bench_current_time - bench_last_time) / 1000;
}

u64 stop_bench_s() {
    bench_current_time = get_system_timer();
    return (bench_current_time - bench_last_time) / 1000000;
}


