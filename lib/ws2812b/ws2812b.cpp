#include "ws2812b.h"

WS2812B::WS2812B(uint16_t numPixels, uint8_t pin)
    : _strip(numPixels, pin, NEO_GRB + NEO_KHZ800) {}

void WS2812B::begin() {
    _strip.begin();
    _strip.show(); // Initialize all pixels to 'off'
    _strip.setBrightness(20);
}

void WS2812B::update() {
    unsigned long current_millis = millis();
    if (current_millis - _last_update >= _wait_ms) {
        _last_update = current_millis;

        for (uint16_t i = 0; i < _strip.numPixels(); i++) {
            _strip.setPixelColor(i, _strip.ColorHSV((i * 65536 / _strip.numPixels() + _rainbow_j * 256) % 65536));
        }
        _strip.show();

        _rainbow_j++;
        if (_rainbow_j >= 256) {
            _rainbow_j = 0;
        }
    }
}