#include "libesp.h"

extern int main(void);

enum {
    SYSTEM_CPU_PER_CONF = ESP32C3_SYSTEM + 0x8,
    SYSTEM_SYSCLK_CONF = ESP32C3_SYSTEM + 0x58
};

static inline void zero_bss(void) {
    extern char _sbss, _ebss;
    for (char *p = &_sbss; p < &_ebss; p++) {
        *p = '\0';
    }
}

// provided by ROM and linked by linker script
void ets_update_cpu_frequency(int f);

static inline void clock_setup(void) {
    // Setup clocks, TRM section 6.2.4.1
    uint32_t per_conf = get32(SYSTEM_CPU_PER_CONF);
    per_conf &= ~(0b10); // clear bit 1
    per_conf |= 0b101;   // set bits 0 and 2
    put32(SYSTEM_CPU_PER_CONF, per_conf);

    // prescale to 40, use PLL clock
    // TRM register 14.10, tables 6-2 and 6-4
    uint32_t sysclk_conf = (1 << 19) | (40 << 12) | (1 << 10);
    put32(SYSTEM_SYSCLK_CONF, sysclk_conf);
    ets_update_cpu_frequency(160);
}

// Initialise memory and other low level stuff, and call main()
void start(void) {
    zero_bss();
    clock_setup();
    main();
}
