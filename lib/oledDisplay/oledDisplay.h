#ifndef OLEDDISPLAY_H
#define OLEDDISPLAY_H

#include <U8g2lib.h>
#include <NTPClient.h>

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

void initOLED();
void showLogo();
void showWiFiInfo();
void showEmoji(int emojiState);
void showWeather(String temperature, String humidity, String weather);
void showTime(NTPClient &client);

#endif
