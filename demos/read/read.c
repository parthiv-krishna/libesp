#include "libesp.h"
#include "gpio.h"
#include "timer.h"
#include "watchdog.h"
#include "uart.h"

#define PIN 7

int main(void) {
    watchdog_disable();
    gpio_set_input(PIN);

    while (1) {
        uart_write(gpio_read(PIN) ? '1' : '0');
    }

    return 0;
}