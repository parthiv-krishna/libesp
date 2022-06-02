#ifndef UART_H
#define UART_H

#include "libesp.h"

/**
 * @brief Initializes the uart on the given pins
 *
 * @param tx_pin The pin to use for transmit
 * @param rx_pin The pin to use for receive
 * @param baud The baud rate to use
 */
void uart_init(int tx_pin, int rx_pin, int baud);

/**
 * @brief Attempts to read a byte from the uart
 *
 * @param c A pointer to the byte to read into
 * @return true A byte was read
 * @return false No byte was available
 */
bool uart_read_nonblocking(uint8_t *c);

/**
 * @brief Reads a byte from the uart, blocking until one is available
 *
 * @param c A pointer to the byte to read into
 * @return true Always returns true
 * @return false Never returns false
 */
bool uart_read_blocking(uint8_t *c);

/**
 * @brief Attempts to write a byte to the uart
 *
 * @param c The byte to write
 * @return true The byte was written
 * @return false The TX FIFO was full
 */
bool uart_write_nonblocking(uint8_t c);

/**
 * @brief Writes a byte to the uart, blocking until the FIFO has space
 *
 * @param c The byte to write
 * @return true Always returns true
 * @return false Never returns false
 */
bool uart_write_blocking(uint8_t c);

// Define this to use nonblocking by default
// #define NONBLOCKING_UART
#ifdef NONBLOCKING_UART
#define uart_read uart_read_nonblocking
#define uart_write uart_write_nonblocking
#else
#define uart_read uart_read_blocking
#define uart_write uart_write_blocking
#endif // NONBLOCKING_UART

#endif // UART_H