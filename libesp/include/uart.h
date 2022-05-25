#ifndef UART_H
#define UART_H

#include "libesp.h"

#include "uart.h"

void uart_init(int tx_pin, int rx_pin, int baud);

uint32_t uart_tx_fifo_len(void);
uint32_t uart_rx_fifo_len(void);

bool uart_read_nonblocking(uint8_t *c);
bool uart_read_blocking(uint8_t *c);

bool uart_write_nonblocking(uint8_t c);
bool uart_write_blocking(uint8_t c);

// #define NONBLOCKING_UART
#ifdef NONBLOCKING_UART
#define uart_read uart_read_nonblocking
#define uart_write uart_write_nonblocking
#else
#define uart_read uart_read_blocking
#define uart_write uart_write_blocking
#endif // NONBLOCKING_UART

#endif // UART_H