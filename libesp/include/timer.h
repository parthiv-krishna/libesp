#ifndef TIMER_H
#define TIMER_H

#include "libesp.h"

/**
 * @brief Gets the number of 16 MHz ticks on the system timer
 *
 * @return uint64_t The number of ticks since the system booted
 */
uint64_t timer_get_ticks(void);

/**
 * @brief Gets the number of microseconds since the system booted
 *
 * @return uint64_t The number of microseconds since the system booted
 */
uint64_t timer_get_us(void);

/**
 * @brief Delays for the given number of microseconds
 *
 * @param us The number of microseconds to delay
 */
void timer_delay_us(uint64_t us);

/**
 * @brief Delays for the given number of milliseconds
 *
 * @param ms The number of milliseconds to delay
 */
void timer_delay_ms(uint64_t ms);

#endif // TIMER_H