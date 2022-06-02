#include "watchdog.h"
#include "ws2812.h"
#include "rgb.h"
#include "gpio.h"
#include "timer.h"

#define PIN 8

int main(void) {
    watchdog_disable();
    gpio_set_output(PIN);

    while(1) {
        for (int h = 0; h < 360; h++) {
            rgb_t color = rgb_from_hsv(h, 100, 100);
            ws2812_display_one(PIN, color);
            timer_delay_ms(10);
        }
    }

    return 0;
}