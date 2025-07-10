
#include "DisplayManager.h"
#include <ESP8266WiFi.h>

DisplayManager::DisplayManager(U8G2 &u8g2) : _u8g2(u8g2) {}

void DisplayManager::init() {
    _u8g2.begin();
}

void DisplayManager::showLogo() {
    _u8g2.clearBuffer();
    _u8g2.drawXBMP(0, (64 / 2 - 22 / 2), 128, 22, logo);
    _u8g2.sendBuffer();
}

void DisplayManager::showWiFiInfo(const char* ssid, const IPAddress& ip) {
    _u8g2.clearBuffer();
    _u8g2.setFont(u8g2_font_ncenB08_tr);
    _u8g2.drawStr(0, 12, "AP Mode");
    _u8g2.drawStr(0, 28, ssid);
    _u8g2.drawStr(0, 44, "IP:");
    _u8g2.drawStr(0, 60, ip.toString().c_str());
    _u8g2.sendBuffer();
}

void DisplayManager::showTime(const String& time) {
    _u8g2.clearBuffer();
    _u8g2.setFont(u8g2_font_ncenB14_tr);
    _u8g2.drawStr(0, 38, time.c_str());
    _u8g2.sendBuffer();
}

void DisplayManager::drawWeatherIcon(const String& weather) {
    if (weather == "阴" || weather == "多云") {
        _u8g2.drawXBMP(0, 0, 64, 64, cloud);
    } else if (weather == "小雨" || weather == "大雨" || weather == "暴雨" || weather == "雨") {
        _u8g2.drawXBMP(0, 0, 64, 64, rain);
    } else if (weather == "晴") {
        _u8g2.drawXBMP(0, 0, 64, 64, sun);
    } else {
        // Default icon or leave blank
    }
}

void DisplayManager::showWeather(const String& temp, const String& humidity, const String& weather) {
    _u8g2.clearBuffer();
    drawWeatherIcon(weather);
    _u8g2.setFont(u8g2_font_ncenB08_tr);
    _u8g2.drawStr(64, 20, "Temp");
    String tempStr = temp + " C";
    _u8g2.drawStr(64, 30, tempStr.c_str());
    _u8g2.drawStr(64, 50, "Humidity");
    String humStr = humidity + " %";
    _u8g2.drawStr(64, 60, humStr.c_str());
    _u8g2.sendBuffer();
}

void DisplayManager::showEmotion(int emotion) {
    const uint8_t* emotion_map[] = {hi, angry, error, dowhat, love, sick, yun, nullptr, nullptr, logo};
    if (emotion >= 0 && emotion < 10 && emotion_map[emotion] != nullptr) {
        _u8g2.clearBuffer();
        _u8g2.drawXBMP(0, 0, 128, 64, emotion_map[emotion]);
        _u8g2.sendBuffer();
    }
}
