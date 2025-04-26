// button.cpp
#include "button.h"

static uint8_t buttonPin;            // 用 static 保存传进来的引脚
volatile bool buttonPressed = false;
unsigned long lastPressTime = 0;
const unsigned long debounceDelay = 50;

void ICACHE_RAM_ATTR handleButtonPress()
{
    unsigned long currentTime = millis();
    if (currentTime - lastPressTime > debounceDelay)
    {
        buttonPressed = true;
        lastPressTime = currentTime;
    }
}

void buttonInit(uint8_t pin)
{
    buttonPin = pin; // 保存传进来的引脚
    pinMode(buttonPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonPress, FALLING);
}

bool buttonCheck()
{
    if (buttonPressed)
    {
        buttonPressed = false;
        return true;
    }
    return false;
}
