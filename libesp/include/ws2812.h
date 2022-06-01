#ifndef WS2812_H
#define WS2812_H

#include "libesp.h"

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_t;

#define RGB_MK(r, g, b) ((rgb_t) {(uint8_t)(r), (uint8_t)(g), (uint8_t)(b)})

typedef struct {
    unsigned pin;
    unsigned num_leds;
    rgb_t pixels[256];
} ws2812_strip_t;

void ws2812_display_one(unsigned pin, rgb_t pixel);

ws2812_strip_t ws2812_strip_init(unsigned pin, int num_leds);
void ws2812_strip_update(ws2812_strip_t *strip);
void ws2812_strip_set_all(ws2812_strip_t *strip, rgb_t pixel);

#endif // WS2812_H