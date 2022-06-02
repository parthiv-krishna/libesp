#include "timer.h"

enum {
    TIMER_UNIT0_OP = ESP32C3_SYSTEM_TIMER + 0x4,
    TIMER_UNT0_HI = ESP32C3_SYSTEM_TIMER + 0x40,
    TIMER_UNT0_LO = ESP32C3_SYSTEM_TIMER + 0x44
};

uint64_t timer_get_ticks(void) {
    // TRM register 10.5: tell timer to write time to regs
    put32(TIMER_UNIT0_OP, 1 << 30);
    while ((get32(TIMER_UNIT0_OP) >> 29) & 1) {
        spin(1);
    } // wait for data ready
    return ((uint64_t)get32(TIMER_UNT0_HI) << 32) | get32(TIMER_UNT0_LO);
}

uint64_t timer_get_us(void) {
    return timer_get_ticks() >> 4; // 16 MHz
}

void timer_delay_us(uint64_t us) {
    uint64_t start = timer_get_us(); // Handler counter wrap
    while (timer_get_us() - us < start) {
        spin(1);
    }
}

void timer_delay_ms(uint64_t ms) { timer_delay_us(ms * 1000); }