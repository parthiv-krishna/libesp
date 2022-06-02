#ifndef GPIO_H
#define GPIO_H

#include "libesp.h"

/**
 * @brief Configures the given pin as an output
 *
 * @param pin The GPIO pin
 */
void gpio_set_output(unsigned pin);

/**
 * @brief Writes the given value to the given pin
 *
 * The pin should be configured as an output
 *
 * @param pin The GPIO pin
 * @param value true (or 1) for high, false (or 0) for low
 */
void gpio_write(unsigned pin, bool value);

/**
 * @brief Toggles the state of the given pin
 *
 * The pin should be configured as an output
 *
 * @param pin The GPIO pin
 */
void gpio_toggle(unsigned pin);

/**
 * @brief Configures the given pin as an input
 *
 * @param pin
 */
void gpio_set_input(unsigned pin);

/**
 * @brief Reads the state of the given pin
 *
 * The pin should be configured as an input
 *
 * @param pin The GPIO pin
 * @return true The pin is high
 * @return false The pin is low
 */
bool gpio_read(unsigned pin);

#endif // GPIO_H