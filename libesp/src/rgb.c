#include "rgb.h"

// https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
rgb_t rgb_from_hsv(int h, uint8_t s, uint8_t v) {
    h = h % 360;
    if (h < 0) {
        h = 360 + h;
    }
    if (s > 100) {
        s = 100;
    }
    if (v > 100) {
        v = 100;
    }

    int C = (v * s); // 0-10000

    int abs = (h % 120 - 60);
    abs = abs < 0 ? -abs : abs;

    int X = C * (60 - abs) / 60;  // 0-10000
    int m = v * 100 - C;          // 0-10000

    int r = 0, g = 0, b = 0;    
    int segment = h / 60;
    switch (segment) {
    case 0:
        r = C;
        g = X;
        break;
    case 1:
        r = X;
        g = C;
        break;
    case 2:
        g = C;
        b = X;
        break;
    case 3:
        g = X;
        b = C;
        break;
    case 4:
        r = X;
        b = C;
        break;
    case 5:
        r = C;
        b = X;
        break;
    };
    return RGB_MK(((r + m) * 255) / 10000,
                  ((g + m) * 255) / 10000,
                  ((b + m) * 255) / 10000);
}