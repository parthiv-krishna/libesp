#ifndef LIBESP_H
#define LIBESP_H

#define NULL 0x0;
typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef unsigned long long uint64_t;
typedef signed long long int64_t;
typedef enum { false = 0, true = 1 } bool;

//////////////////////////////////////////////////
// Module/Peripheral Addresses -- TRM Table 3-4 //
//////////////////////////////////////////////////

enum {
    ESP32C3_UART0 = 0x60000000,
    ESP32C3_SPI1 = 0x60010000,
    ESP32C3_SPI0 = 0x60003000,
    ESP32C3_GPIO = 0x60004000,
    ESP32C3_TIMER = 0x60007000,
    ESP32C3_LOW_POWER_MGMT = 0x60008000,
    ESP32C3_IO_MUX = 0x60009000,
    ESP32C3_UART1 = 0x60010000,
    ESP32C3_I2C = 0x60013000,
    ESP32C3_UHCI0 = 0x60014000,
    ESP32C3_REMOTE_CTRL = 0x60016000,
    ESP32C3_LED_PWM = 0x60019000,
    ESP32C3_EFUSE = 0x6001A000,
    ESP32C3_TIMER_GROUP0 = 0x6001F000,
    ESP32C3_TIMER_GROUP1 = 0x60020000,
    ESP32C3_SYSTEM_TIMER = 0x60023000,
    ESP32C3_SPI2 = 0x60024000,
    ESP32C3_APB = 0x60026000,
    ESP32C3_TWAI = 0x6002B000,
    ESP32C3_I2S = 0x6002D000,
    ESP32C3_AES_ACCEL = 0x6003A000,
    ESP32C3_SHA_ACCEL = 0x6003B000,
    ESP32C3_RSA_ACCEL = 0x6003C000,
    ESP32C3_DIG_SIG = 0x6003D000,
    ESP32C3_HMAC_ACCEL = 0x6003E000,
    ESP32C3_GDMA = 0x6003F000,
    ESP32C3_ADC = 0x60040000,
    ESP32C3_USB_JTAG = 0x60043000,
    ESP32C3_SYSTEM = 0x600C0000,
    ESP32C3_SENSITIVE = 0x600C1000,
    ESP32C3_INTERRUPT = 0x600C2000,
    ESP32C3_CONFIG_CACHE = 0x600C4000,
    ESP32C3_MEM_ENCRYPT = 0x600CC000,
    ESP32C3_ASSIST_DEBUG = 0x600CE000,
    ESP32C3_WORLD = 0x600D0000
};

//////////////////////////////////////
// PUT/GET32 -- defined in putget.S //
//////////////////////////////////////
void put32_asm(uint32_t addr, uint32_t val);
uint32_t get32_asm(uint32_t addr);

/**
 * @brief nop for the given number of cycles
 *
 * @param numiters the number of cycles
 */
static inline void spin(unsigned numiters) {
    while (numiters--) {
        asm volatile("nop");
    }
}

// uncomment to use the asm version, but it's slower
#define INLINE_PUTGET
#ifdef INLINE_PUTGET
#define put32(addr, val) *(volatile uint32_t *)(addr) = (val)
#define get32(addr) *(volatile uint32_t *)(addr)
#else // !INLINE_PUTGET
#define put32(addr, val) put32_asm((uint32_t)(addr), (uint32_t)(val))
#define get32(addr) get32_asm((uint32_t)(addr))
#endif // INLINE_PUTGET

#endif // LIBESP_H