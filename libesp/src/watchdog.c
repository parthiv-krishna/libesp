#include "watchdog.h"

enum {
    WATCHDOG_CNTL_DIG_ISO = ESP32C3_LOW_POWER_MGMT + 0x8C,
    WATCHDOG_CONFIG0 = ESP32C3_LOW_POWER_MGMT + 0x90,
    WATCHDOG_WKEY = ESP32C3_LOW_POWER_MGMT + 0xA8,
    WATCHDOG_WKEY_MAGICNUM = 0x50D83AA1,

    SUPERWATCHDOG_CONFIG = ESP32C3_LOW_POWER_MGMT + 0xAC,
    SUPERWATCHDOG_WKEY = ESP32C3_LOW_POWER_MGMT + 0xB0,
    SUPERWATCHDOG_CPU_STALL = ESP32C3_LOW_POWER_MGMT + 0xB4,
    SUPERWATCHDOG_WKEY_MAGICNUM = 0x8F1D312A,

    TIMER0_WDT_CONFIG = ESP32C3_TIMER_GROUP0 + 0x48,
    TIMER1_WDT_CONFIG = ESP32C3_TIMER_GROUP1 + 0x48,
    TIMER0_REGCLK = ESP32C3_TIMER_GROUP0 + 0xFC
};

void watchdog_disable(void) {
    // Watchdog
    put32(WATCHDOG_WKEY, WATCHDOG_WKEY_MAGICNUM); // Disable write protection
    put32(WATCHDOG_CONFIG0, 0);                   // Disable watchdog
    put32(WATCHDOG_CNTL_DIG_ISO, 0);

    // Superwatchdog
    put32(SUPERWATCHDOG_WKEY, SUPERWATCHDOG_WKEY_MAGICNUM); // Write protec
    uint32_t swd_config = get32(SUPERWATCHDOG_CONFIG); // Disable superwatchdog
    swd_config |= (1 << 31);
    put32(SUPERWATCHDOG_CONFIG, swd_config);
    put32(SUPERWATCHDOG_CPU_STALL, 0);

    // (TRM section 11 register 11.26)
    uint32_t timer0_regclk = get32(TIMER0_REGCLK);
    timer0_regclk &= ~(1 << 9); // disable TIMG_WDT
    put32(TIMER0_REGCLK, timer0_regclk);
    // Disable timer group 0/1 watchdog (TRM section 11 register 11.10)
    put32(TIMER0_WDT_CONFIG, 0);
    put32(TIMER1_WDT_CONFIG, 0);
}