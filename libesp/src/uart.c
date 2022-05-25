#include "uart.h"

#define UART_FIFO_MAX_SIZE 4

enum {
    UART_FIFO = ESP32C3_UART0 + 0x0,
    UART_CLKDIV = ESP32C3_UART0 + 0x14,
    UART_STATUS = ESP32C3_UART0 + 0x1C,
    UART_CONF0 = ESP32C3_UART0 + 0x20,
    UART_CONF1 = ESP32C3_UART0 + 0x24,
    UART_CLKCONF = ESP32C3_UART0 + 0x78
};

enum {
    GPIO_OUT_EN = ESP32C3_GPIO + 0x20,
    GPIO_OUT_FUNC_BASE = ESP32C3_GPIO + 0x554,
    GPIO_FUNC_UART_SEL = ESP32C3_GPIO + 0x154 + 4*6
};

enum {
    IO_MUX_BASE = ESP32C3_IO_MUX + 0x4
};

void uart_init(int tx_pin, int rx_pin, int baud) {    
    // Setup clock divider from baud TRM register 24.7
    uint32_t div = ((uint32_t)4000 * 1000000 / (uint32_t)baud);
    uint32_t clkdiv = div / 100;                // integer
    clkdiv |= (16 * (div % 100) / 100) << 20;   // fractional

    // disable UART while setting up: TRM register 24.9
    uint32_t conf0 = get32(UART_CONF0);
    conf0 &= ~(1 << 28); // disable UART_MEM_CLK_EN
    conf0 |= (1 << 26); // enable UART_ERR_WR_MASK
    put32(UART_CONF0, conf0);

    // setup UART interrupts: TRM register 24.10
    put32(UART_CONF1, 0x1); // RXFULL 1, TXFULL 0

    // setup UART clock to drive TX, RX with XTAL clock (bits 25, 24, 22, 21, 10)
    put32(UART_CLKCONF, 0b110111 << 20);

    // Set TX pin
    uint32_t out_en = get32(GPIO_OUT_EN);
    out_en |= (1 << tx_pin);
    put32(GPIO_OUT_EN, out_en);

    uint32_t func_base = get32(GPIO_OUT_FUNC_BASE + tx_pin * sizeof(uint32_t));
    func_base &= ~0xff;
    func_base |= 6;
    put32(GPIO_OUT_FUNC_BASE + tx_pin * sizeof(uint32_t), func_base);

    // Set RX pin
    out_en = get32(GPIO_OUT_EN);
    out_en &= ~(1 << rx_pin);
    put32(GPIO_OUT_EN, out_en);

    put32(IO_MUX_BASE + rx_pin * sizeof(uint32_t), 0b11 << 8); // input, pullup
    put32(GPIO_FUNC_UART_SEL, (1 << 6) | rx_pin);
}

uint32_t uart_tx_fifo_len() {
    return (get32(UART_STATUS) >> 16) & 127;
}

uint32_t uart_rx_fifo_len() {
    return get32(UART_STATUS) & 127;
}

bool uart_read_nonblocking(uint8_t *c) {
    if (uart_rx_fifo_len() == 0) {
        return false;
    }
    *c = get32(UART_FIFO) & 255;
    return true;
}

bool uart_read_blocking(uint8_t *c) {
    while (!uart_read(c)) { spin(1); }
    return true;
}

bool uart_write_nonblocking(uint8_t c) {
    if (uart_tx_fifo_len() >= UART_FIFO_MAX_SIZE) {
        return false;
    }
    put32(UART_FIFO, c);
    return true;
}

bool uart_write_blocking(uint8_t c) {
    while (!uart_write_nonblocking(c)) { spin(1); }
    return true;
}

