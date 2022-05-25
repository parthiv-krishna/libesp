#ifndef TIMER_H
#define TIMER_H

#include "libesp.h"

uint64_t timer_get_ticks(void);

uint64_t timer_get_us(void);

void timer_delay_us(uint64_t us);

void timer_delay_ms(uint64_t ms);

#endif // TIMER_H