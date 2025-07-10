#ifndef WS2812B_H
#define WS2812B_H

#include <Adafruit_NeoPixel.h>

class WS2812B {
public:
    WS2812B(uint16_t numPixels, uint8_t pin);
    void begin();
    void update(); // Changed from showRainbow

private:
    Adafruit_NeoPixel _strip;
    uint16_t _rainbow_j = 0;
    unsigned long _last_update = 0;
    uint8_t _wait_ms = 2; // Animation delay
};

#endif // WS2812B_H