#include "ws2812.h"

#include "gpio.h"
#include "timer.h"

static inline void write_byte(unsigned pin, uint8_t byte) {
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

static inline void write_pixel(unsigned pin, rgb_t pixel) {
    write_byte(pin, pixel.g);
    write_byte(pin, pixel.r);
    write_byte(pin, pixel.b);
}

static inline void set_signal(unsigned pin) {
    gpio_write(pin, false);
    timer_delay_us(500);
}

void ws2812_display_one(unsigned pin, rgb_t pixel) {
    write_pixel(pin, pixel);
    set_signal(pin);
}

ws2812_strip_t ws2812_strip_init(unsigned pin, int num_leds) {
    gpio_set_output(pin);

    return (ws2812_strip_t){
        .pin = pin,
        .num_leds = num_leds,
    };
}

void ws2812_strip_update(ws2812_strip_t *strip) {
    for (int i = 0; i < strip->num_leds; i++) {
        write_pixel(strip->pin, strip->pixels[i]);
    }
    set_signal(strip->pin);
}

void ws2812_strip_set_all(ws2812_strip_t *strip, rgb_t pixel) {
    for (int i = 0; i < strip->num_leds; i++) {
        strip->pixels[i] = pixel;
    }
}