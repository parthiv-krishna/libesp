#include "libesp.h"
#include "gpio.h"
#include "timer.h"
#include "watchdog.h"

#define PIN 8

int main(void) {
    watchdog_disable();
    gpio_set_output(PIN);

    while (1) {
        gpio_write(PIN, true);
        timer_delay_ms(1000);

        gpio_write(PIN, false);
        timer_delay_ms(500);
    }

    return 0;
}