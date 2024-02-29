#ifndef COLOR_CONVERTER_H
#define COLOR_CONVERTER_H

#include "Arduino.h"

static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

// C++ implementation of HSL to RGB conversion
// Algorithm source: https://en.wikipedia.org/wiki/HSL_and_HSV#HSL_to_RGB_alternative
static uint32_t hsl2RGB (float h, float s, float l){
    uint8_t r,g,b;

    float c = (1 - abs(2 * l - 1)) * s;
    float x = c * (1 - abs(fmod(h / 60.0, 2) - 1));
    float m = l - c / 2;

    if (h < 60) {
        r = (c + m) * 255;
        g = (x + m) * 255;
        b = m * 255;
    } else if (h < 120) {
        r = (x + m) * 255;
        g = (c + m) * 255;
        b = m * 255;
    } else if (h < 180) {
        r = m * 255;
        g = (c + m) * 255;
        b = (x + m) * 255;
    } else if (h < 240) {
        r = m * 255;
        g = (x + m) * 255;
        b = (c + m) * 255;
    } else if (h < 300) {
        r = (x + m) * 255;
        g = m * 255;
        b = (c + m) * 255;
    } else {
        r = (c + m) * 255;
        g = m * 255;
        b = (x + m) * 255;
    }

    return Color(r,g,b);

}

#endif
