#ifndef GPIO_H
#define GPIO_H

#include "libesp.h"

typedef enum {
    GPIO_MODE_INPUT, 
    GPIO_MODE_OUTPUT
} gpio_mode_t;

void gpio_set_input(int pin);
void gpio_set_output(int pin);
void gpio_set_mode(int pin, gpio_mode_t mode);

void gpio_write(int pin, bool value);

#endif // GPIO_H