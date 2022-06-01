#ifndef WS2812_H
#define WS2812_H

#include "libesp.h"

// increase to use more than 256 LEDs
// eventually implement malloc and then won't need
#define MAX_NLEDS 256

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_t;

#define RGB_MK(r, g, b) ((rgb_t) {(uint8_t)(r), (uint8_t)(g), (uint8_t)(b)})

typedef struct {
    unsigned pin;
    unsigned num_leds;
    rgb_t pixels[MAX_NLEDS];
} ws2812_strip_t;

/**
 * @brief Displays a color on a single WS2812 (useful for builtin RBG LED)
 * 
 * The pin should be configured as an output
 * 
 * @param pin The pin which the WS2812 is connected to
 * @param pixel The color to display
 */
void ws2812_display_one(unsigned pin, rgb_t pixel);

/**
 * @brief Initializes an WS2812 strip
 * 
 * @param pin The pin which the WS2812 strip is connected to
 * @param num_leds The number of LEDs in the strip
 * @return ws2812_strip_t WS2812 strip handle
 */
ws2812_strip_t ws2812_strip_init(unsigned pin, int num_leds);

/**
 * @brief Updates the colors on the physical strip from the data in memory
 * 
 * @param strip The WS2812 strip handle
 */
void ws2812_strip_update(ws2812_strip_t *strip);

/**
 * @brief Sets the color of all LEDs in the strip to the same color
 * 
 * @param strip The WS2812 strip handle
 * @param pixel The color to display
 */
void ws2812_strip_set_all(ws2812_strip_t *strip, rgb_t pixel);

#endif // WS2812_H