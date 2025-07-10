
#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include "image.h"

class DisplayManager {
public:
    DisplayManager(U8G2 &u8g2);
    void init();
    void showLogo();
    void showWiFiInfo(const char* ssid, const IPAddress& ip);
    void showTime(const String& time);
    void showWeather(const String& temp, const String& humidity, const String& weather);
    void showEmotion(int emotion);

private:
    U8G2& _u8g2;
    void drawWeatherIcon(const String& weather);
};

#endif // DISPLAYMANAGER_H
