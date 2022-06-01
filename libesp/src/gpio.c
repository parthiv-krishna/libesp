#include "gpio.h"

enum {
    GPIO_IN = ESP32C3_GPIO + 0x3C,
    GPIO_OUT = ESP32C3_GPIO + 0x4,
    GPIO_OUT_EN = ESP32C3_GPIO + 0x20,
    GPIO_OUT_FUNC_BASE = ESP32C3_GPIO + 0x554
};

void gpio_set_output(unsigned pin) {
    // TRM section 5.5.3
    uint32_t func_reg_addr = GPIO_OUT_FUNC_BASE + pin * sizeof(uint32_t);
    put32(func_reg_addr, (1 << pin) | 128);

    // enable output
    uint32_t out_en = get32(GPIO_OUT_EN);
    out_en |= (1 << pin); // enable output on pin
    put32(GPIO_OUT_EN, out_en);
}

void gpio_write(unsigned pin, bool value) {
    uint32_t out = get32(GPIO_OUT);
    out &= ~(1 << pin);    // clear existing
    out |= (~value << pin); // set new
    put32(GPIO_OUT, out);
}

void gpio_toggle(unsigned pin) {
    uint32_t out = get32(GPIO_OUT);
    out ^= (1 << pin); // toggle
    put32(GPIO_OUT, out);
}

void gpio_set_input(unsigned pin) {
    // disable output
    uint32_t out_en = get32(GPIO_OUT_EN);
    out_en &= ~(1 << pin); // clear bit
    put32(GPIO_OUT_EN, out_en);
}

bool gpio_read(unsigned pin) {
    // TRM section 5.4.4
    uint32_t in = get32(GPIO_IN);
    return (in >> pin) & 1;
}
