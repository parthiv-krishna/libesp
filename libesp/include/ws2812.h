#ifndef WS2812_H
#define WS2812_H

#include "libesp.h"
#include "gpio.h"
#include "timer.h"

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_t;


void ws2812_show(int pin, const rgb_t pixel);

#endif // WS2812_H