#include "libesp.h"
#include "watchdog.h"
#include "fft.h"
#include "log.h"
#include "timer.h"


#define LOG2_N 4
#define N (1 << LOG2_N)

void print_complex_arr(q15_t *real, q15_t *imag, int n) {
    for (int i = 0; i < n; i++) {
        log_putd(i);
        log_puts(": ");
        log_putd(real[i]);
        log_puts(" + ");
        log_putd(imag[i]);
        log_puts("j\r\n");
    }
}

int main(void) {

    watchdog_disable();
    
    q15_t real[N] = {1024,-1024,1024,-1024,1024,-1024,1024,-1024,1024,-1024,1024,-1024,1024,-1024,1024,-1024};
    q15_t imag[N] = {0};
    timer_delay_ms(500);
    log_puts("IN\r\n");
    print_complex_arr(real, imag, N);

    log_puts("\nFWD\r\n");
    fft_fixed_cfft(real, imag, LOG2_N, 0);
    print_complex_arr(real, imag, N);

    log_puts("\nINV\r\n");
    fft_fixed_cfft(real, imag, LOG2_N, 1);
    print_complex_arr(real, imag, N);

    return 0;
}

