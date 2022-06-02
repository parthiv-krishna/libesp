#ifndef LOG_H
#define LOG_H

#include "libesp.h"
#include "uart.h"

// redefine to log in some other way
static inline void log_putc(char c) {
    uart_write_blocking((uint8_t) c);
}

void log_puts(const char *s);

void log_putx(uint32_t v);

void log_putp(void *p);

void log_putd(int32_t v);

#endif // LOG_H