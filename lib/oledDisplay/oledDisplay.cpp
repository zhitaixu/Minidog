#include "oledDisplay.h"
#include "image.h"

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/5, /* data=*/4);

void initOLED() {
    u8g2.begin();
    u8g2.setDisplayRotation(U8G2_R2);
}

void showLogo() {
    u8g2.firstPage();
    do {
        u8g2.setFont(u8g2_font_ncenB14_tr);
        u8g2.drawXBMP(0, (64 / 2 - 22 / 2), 128, 22, logo);
    } while (u8g2.nextPage());
}

void showWiFiInfo() {
    u8g2.clearDisplay();
    u8g2.firstPage();
    do {
        u8g2.setFont(u8g2_font_ncenB08_tr);
        u8g2.drawXBMP(0, 0, 64, 64, wifi);
        u8g2.drawStr(64, 10, "WIFI_AP");
        u8g2.drawStr(64, 27, "EDA-Robot");
        u8g2.drawStr(64, 43, "192.168.4.1");
        u8g2.drawStr(64, 60, "WIFI CTRL");
    } while (u8g2.nextPage());
}

void showEmoji(int emojiState) {
    u8g2.clearDisplay();
    u8g2.firstPage();
    const unsigned char* emojiBitmap = nullptr;
    switch (emojiState) {
        case 0: emojiBitmap = hi; break;
        case 1: emojiBitmap = angry; break;
        case 2: emojiBitmap = error; break;
        case 3: emojiBitmap = dowhat; break;
        case 4: emojiBitmap = love; break;
        case 5: emojiBitmap = sick; break;
        case 6: emojiBitmap = yun; break;
        case 9: emojiBitmap = logo; break;
        default: return;
    }

    do {
        u8g2.setFont(u8g2_font_ncenB14_tr);
        u8g2.drawXBMP(0, 0, 128, 64, emojiBitmap);
    } while (u8g2.nextPage());
}

void showWeather(String temperature, String humidity, String weather) {
    const unsigned char* icon = nullptr;
    if (weather == "阴" || weather == "多云") icon = cloud;
    else if (weather.indexOf("雨") != -1) icon = rain;
    else if (weather == "晴") icon = sun;

    u8g2.clearDisplay();
    u8g2.firstPage();
    do {
        u8g2.setFont(u8g2_font_ncenB08_tr);
        if (icon != nullptr) u8g2.drawXBMP(0, 0, 64, 64, icon);
        u8g2.drawStr(64, 20, "Temp");
        u8g2.drawStr(64, 30, (temperature + " C").c_str());
        u8g2.drawStr(64, 50, "Humidity");
        u8g2.drawStr(64, 60, (humidity + " %").c_str());
    } while (u8g2.nextPage());
}

void showTime(NTPClient &client) {
    client.update();
    int hour = client.getHours();
    int minute = client.getMinutes();
    String timeStr = String(hour) + ":" + (minute < 10 ? "0" : "") + String(minute);

    u8g2.clearDisplay();
    u8g2.firstPage();
    do {
        u8g2.setFont(u8g2_font_ncenB14_tr);
        u8g2.drawXBMP(0, 0, 64, 64, timeimage);
        u8g2.drawStr(64, 30, "TIME");
        u8g2.setCursor(64, 50);
        u8g2.print(timeStr);
    } while (u8g2.nextPage());
}
