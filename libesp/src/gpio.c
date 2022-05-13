#include "gpio.h"

enum { 
    GPIO_OUT_REG = ESP32C3_GPIO + 0x4,
    GPIO_OUT_EN = ESP32C3_GPIO + 0x20, 
    GPIO_OUT_FUNC_BASE = ESP32C3_GPIO + 0x554,
    GPIO_IN_FUNC = 85 
};

void gpio_set_input(int pin) {
    // disable output
    uint32_t gpio_out_en = get32(GPIO_OUT_EN);
    gpio_out_en &= ~(1 << pin);
    put32(GPIO_OUT_EN, gpio_out_en);
}

void gpio_set_output(int pin) {
    // TRM 5.5.3: configure pin function to respond to GPIO_OUT_EN
    put32(GPIO_OUT_FUNC_BASE + pin*sizeof(uint32_t), (1 << 9) | 0x80);
}

void gpio_set_mode(int pin, gpio_mode_t mode) {
    if (mode == GPIO_MODE_INPUT) {
        gpio_set_input(pin);
    } else if (mode == GPIO_MODE_OUTPUT) {
        gpio_set_output(pin);
    }
}

void gpio_write(int pin, bool value) {
    // enable output
    uint32_t gpio_out_reg = get32(GPIO_OUT_REG);
    gpio_out_reg &= ~(1 << pin); // clear
    gpio_out_reg |= (value ? 1 : 0) << pin;
    put32(GPIO_OUT_REG, gpio_out_reg);
}

// void gpio_toggle(int pin) { REG(C3_GPIO)[1] ^= BIT(pin); }

// bool gpio_read(int pin) { return REG(C3_GPIO)[15] & BIT(pin) ? 1 : 0; }
