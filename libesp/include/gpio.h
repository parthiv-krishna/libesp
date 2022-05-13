#ifndef GPIO_H
#define GPIO_H

#include "libesp.h"

void gpio_set_output(int pin);
void gpio_write(int pin, bool value);
void gpio_toggle(int pin);

void gpio_set_input(int pin);
bool gpio_read(int pin);

#endif // GPIO_H