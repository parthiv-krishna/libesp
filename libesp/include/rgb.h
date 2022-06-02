#ifndef RGB_H
#define RGB_H

#include "libesp.h"

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_t;

#define RGB_MK(r, g, b) ((rgb_t){(uint8_t)(r), (uint8_t)(g), (uint8_t)(b)})

/**
 * @brief Creates an RGB color from HSV
 * 
 * @param h Hue
 * @param s Saturation
 * @param v Value
 * @return rgb_t RGB color
 */
rgb_t rgb_from_hsv(int h, uint8_t s, uint8_t v);


#define RGB_BLACK RGB_MK(0, 0, 0)
#define RGB_RED RGB_MK(255, 0, 0)
#define RGB_GREEN RGB_MK(0, 255, 0)
#define RGB_BLUE RGB_MK(0, 0, 255)
#define RGB_CYAN RGB_MK(0, 255, 255)
#define RGB_MAGENTA RGB_MK(255, 0, 255)
#define RGB_YELLOW RGB_MK(255, 255, 0)
#define RGB_WHITE RGB_MK(255, 255, 255)

#endif // RGB_H