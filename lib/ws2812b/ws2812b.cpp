#include <ws2812b.h>

WS2812B::WS2812B(uint16_t numPixels, uint8_t pin)
    : strip(numPixels, pin, NEO_GRB + NEO_KHZ800) {}

void WS2812B::begin() {
    strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
    strip.show();  // Initialize all pixels to 'off'
    strip.setBrightness(20);
}


void WS2812B::rainbowCycle(uint8_t wait){
    uint16_t i, j;

    for (j = 0; j < 256 * 1; j++) { // 5 cycles of all colors on the wheel
        for (i = 0; i < strip.numPixels(); i++) {
            // strip.setPixelColor(i, strip.ColorHSV((i * 256 / strip.numPixels() + j) & 255));
            strip.setPixelColor(i, strip.ColorHSV((i * 65536 / strip.numPixels() + j * 256) % 65536));
        }
        strip.show();
        delay(wait);
    }
}

void WS2812B::showRainbow(uint8_t wait) {
    rainbowCycle(wait);
}
