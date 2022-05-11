#ifndef LIBESP_H
#define LIBESP_H

// TRM Table 3-4: Module/Peripheral Address Mapping
enum {
    ESP32C3_UART0 = 0x6000'0000,
    ESP32C3_SPI1 = 0x6001'0000,
    ESP32C3_SPI0 = 0x6000'3000,
    ESP32C3_GPIO = 0x6000'4000,
    ESP32C3_TIMER = 0x6000'7000,
    ESP32C3_LOW_POWER_MGMT = 0x6000'9000,
    ESP32C3_IO_MUX = 0x6000'9000,
    ESP32C3_UART1 = 0x6001'0000,
    ESP32C3_I2C = 0x6001'3000,
    ESP32C3_UHCI0 = 0x6001'4000,
    ESP32C3_REMOTE_CTRL = 0x6001'6000,
    ESP32C3_LED_PWM = 0x6001'9000,
    ESP32C3_EFUSE = 0x6001'A000,
    ESP32C3_TIMER_GROUP0 = 0x6001'F000,
    ESP32C3_TIMER_GROUP1 = 0x6002'0000,
    ESP32C3_SYSTEM_TIMER = 0x6002'3000,
    ESP32C3_SPI2 = 0x6002'4000,
    ESP32C3_APB = 0x6002'6000,
    ESP32C3_TWAI = 0x6002'B000,
    ESP32C3_I2S = 0x6002'D000,
    ESP32C3_AES_ACCEL = 0x6003'A000,
    ESP32C3_SHA_ACCEL = 0x6003'B000,
    ESP32C3_RSA_ACCEL = 0x6003'C000,
    ESP32C3_DIG_SIG = 0x6003'D000,
    ESP32C3_HMAC_ACCEL = 0x6003'E000,
    ESP32C3_GDMA = 0x6003'F000,
    ESP32C3_ADC = 0x6004'0000,
    ESP32C3_USB_JTAG = 0x6004'3000,
    ESP32C3_SYSTEM = 0x600C'0000,
    ESP32C3_SENSITIVE = 0x600C'1000,
    ESP32C3_INTERRUPT = 0x600C'2000,
    ESP32C3_CONFIG_CACHE = 0x600C'4000,
    ESP32C3_MEM_ENCRYPT = 0x600C'C000,
    ESP32C3_ASSIST_DEBUG = 0x600C'E000,
    ESP32C3_WORLD = 0x600D'0000
};

#endif // LIBESP_H