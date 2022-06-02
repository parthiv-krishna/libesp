#include "log.h"

void log_puts(const char *buf) {
    while (*buf != '\0') {
        log_putc(*buf++);
    }
}

static inline uint8_t to_x(uint32_t c) {
    uint8_t cc = (uint8_t)c;
    return (cc < 10 ? '0' + cc : 'a' + (cc - 10));
}

static inline uint8_t to_d(uint8_t c) {
    return '0' + (uint8_t)c;
}

void log_putx(uint32_t v) {
    unsigned curr = sizeof(v) * 8;
    bool displayed = false;
    while (curr) {
        curr -= 4;
        uint8_t c = (v >> curr) & 15;
        if (displayed || c != 0) {
            log_putc(to_x(c));
            displayed = true;
        }
    }
    if (!displayed) {
        log_putc(to_x(0));
    }
}

void log_putp(void *p) {
    uint32_t pp = (uint32_t)p;
    unsigned curr = sizeof(pp) * 8;
    log_puts("0x");
    while (curr) {
        curr -= 4;
        uint8_t c = (pp >> curr) & 15;
        log_putc(to_x(c));
    }
}

void log_putd(int32_t v) {
    if (v < 0) {
        log_putc('-');
        v = -v;
    }
    int32_t div = 1000000000; // largest power of 10 < INT32_MAX
    while (v < div) {
        div /= 10; // figure out how many digits needed
    }
    while (div > 0) {
        int32_t digit = v / div;
        v -= digit * div;
        div /= 10;
        log_putc(to_d(digit));
    }
}
