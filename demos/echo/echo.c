#include "libesp.h"
#include "uart.h"
#include "watchdog.h"

#define BUFLEN 64

int main(void) {
    watchdog_disable();
    uint8_t buf[BUFLEN];
    int i = 0;
    while (1) {
        if (uart_read(&buf[i])) {
            uart_write(buf[i]);
            if (buf[i++] == '\r') { // screen sends \r not \n
                uart_write('\n');
                for (int j = 0; j < i; j++) {
                    uart_write(buf[j]);
                }
                uart_write('\n');
                i = 0;
            }
        }
    }

    return 0;
}
