#ifndef WS2812_H
#define WS2812_H

#include "libesp.h"

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_t;


void ws2812_display_one(int pin, const rgb_t pixel);

#endif // WS2812_H