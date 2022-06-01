#include "ws2812.h"

#include "gpio.h"
#include "timer.h"

static inline void write_byte(int pin, uint8_t byte) {
     // gives right timing, found with logic analyzer
    unsigned delays[2] = {22, 6};
    for (uint8_t mask = 0x80; mask; mask >>= 1) {
        int i = (byte & mask) ? 0 : 1;
        gpio_write(pin, true);
        spin(delays[i]);
        gpio_write(pin, false);
        spin(delays[1 - i]);
    }
}

void ws2812_show(int pin, const rgb_t pixels) {
    write_byte(pin, pixels.g);
    write_byte(pin, pixels.r);
    write_byte(pin, pixels.b);
}