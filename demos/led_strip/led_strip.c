#include "libesp.h"
#include "ws2812.h"
#include "rgb.h"
#include "timer.h"
#include "watchdog.h"

#define PIN 8
#define NUM_LEDS 256

int main(void) {
    watchdog_disable();

    ws2812_strip_t strip;
    ws2812_strip_init(&strip, PIN, NUM_LEDS);

    rgb_t colors[360];
    for (int h = 0; h < 360; h++) {
        colors[h] = rgb_from_hsv(h, 100, 100);
    }

    while (1) {
        for (int h = 0; h < 360; h++) {
            for (int i = 0; i < NUM_LEDS; i++) {
                ws2812_strip_set(&strip, i, colors[(h + i) % 360]);
            }
            ws2812_strip_update(&strip);
        }
    }
}