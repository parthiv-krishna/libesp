#include "libesp.h"
#include "log.h"
#include "watchdog.h"
#include "timer.h"

int main(void) {
    watchdog_disable();

    timer_delay_ms(500);

    for (int i = 0; i < 31; i++) {
        log_putp((void*)i);
        log_puts(": ");
        log_putx(1 << i);
        log_putc(' ');
        log_putd(1 << i);
        log_puts("\r\n");
    }
}