#ifndef GPIO_H
#define GPIO_H

#include "libesp.h"

void gpio_set_output(unsigned pin);
void gpio_write(unsigned pin, bool value);
void gpio_toggle(unsigned pin);

void gpio_set_input(unsigned pin);
bool gpio_read(unsigned pin);

#endif // GPIO_H