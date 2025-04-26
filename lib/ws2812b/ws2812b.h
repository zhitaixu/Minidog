#ifndef WS2812B_H
#define WS2812B_H

#include <Adafruit_NeoPixel.h>

class WS2812B{
public:
    WS2812B(uint16_t numPixels, uint8_t pin);
    void begin();
    void showRainbow(uint8_t Wait);

private:
    Adafruit_NeoPixel strip;
    void rainbowCycle(uint8_t wait);
};

#endif

