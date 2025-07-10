#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "config.h"
#include "WiFiManager.h"
#include "DisplayManager.h"
#include "servofoot.h" 
#include "WeatherService.h"
#include "ws2812b.h"
#include "button.h"
#include "adc.h"
#include "WebServerManager.h"

// --- Global Objects ---
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, NTP_TIME_OFFSET, NTP_UPDATE_INTERVAL);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

WiFiManager wifiManager(SSID_FILE);
DisplayManager displayManager(u8g2);
ActionSequencer actionSequencer(ENGINE1_PIN, ENGINE2_PIN, ENGINE3_PIN, ENGINE4_PIN);
WeatherService weatherService("", ""); // Initialized empty

// --- State & Data Cache ---
int actionstate = 0;
int emojiState = 0;
int speed = INITIAL_SPEED;
bool freestate = false;
float batteryVoltage = 0.0;
int batteryPercentage = 0;
String useruid, cityname, weatherapi;

// Cached data for non-blocking display
WeatherData cachedWeatherData;
String cachedFormattedTime;

WebServerManager webServerManager(actionstate, emojiState, speed, freestate, useruid, cityname, weatherapi, batteryVoltage, batteryPercentage);
WS2812B ledStrip(PIXEL_COUNT, PIXEL_PIN);

// --- Background Task Timers ---
unsigned long lastWeatherUpdateTime = 0;
unsigned long lastNTPUpdateTime = 0;
const unsigned long WEATHER_UPDATE_INTERVAL = 15 * 60 * 1000; // 15 minutes
const unsigned long NTP_UPDATE_INTERVAL_LOOP = 60 * 1000; // 1 minute

void setup() {
    Serial.begin(115200);

    // Hardware Init
    ledStrip.begin();
    buttonInit(BUTTON_PIN);
    initAdcSampler();
    actionSequencer.begin();
    displayManager.init();
    displayManager.showLogo();
    delay(2000); // Keep a short delay for logo visibility

    // Services Init
    if (wifiManager.loadConfig()) {
        useruid = wifiManager.getUID();
        cityname = wifiManager.getCity();
        weatherapi = wifiManager.getAPIKey();
        weatherService.reconfigure(weatherapi, cityname);
        timeClient.begin();
    } else {
        wifiManager.setupAP(AP_SSID, AP_PASSWORD);
    }

    webServerManager.begin();

    if (wifiManager.isConnected()) {
        timeClient.update();
        cachedFormattedTime = timeClient.getFormattedTime();
        displayManager.showTime(cachedFormattedTime);
    } else {
        displayManager.showWiFiInfo(AP_SSID, WiFi.softAPIP());
    }
}

void handleBackgroundTasks() {
    if (!wifiManager.isConnected()) return;

    unsigned long currentMillis = millis();

    // --- NTP Update Task ---
    if (currentMillis - lastNTPUpdateTime >= NTP_UPDATE_INTERVAL_LOOP) {
        lastNTPUpdateTime = currentMillis;
        if (timeClient.update()) {
            cachedFormattedTime = timeClient.getFormattedTime();
            Serial.println("NTP time updated in background.");
        }
    }

    // --- Weather Update Task ---
    if (currentMillis - lastWeatherUpdateTime >= WEATHER_UPDATE_INTERVAL) {
        lastWeatherUpdateTime = currentMillis;
        if (weatherService.fetchWeather(cachedWeatherData)) {
            Serial.println("Weather data updated in background.");
        }
    }
}

void loop() {
    // --- Real-time, non-blocking updates ---
    actionSequencer.update();
    ledStrip.update();
    updateAdcSampler();

    // --- Background data fetching ---
    handleBackgroundTasks();

    // --- Sensor and Input Handling ---
    if (isAdcSamplingDone()) {
        float adcVoltage = getLastAverageVoltage();
        batteryVoltage = adcVoltage * voltageDividerRatio;
        batteryPercentage = mapBatteryPercentage(batteryVoltage);
    }

    if (buttonCheck()) {
        actionSequencer.startAction(ACTION_FRONT);
    }

    // --- State Machine for Actions & Emotions ---
    if (actionstate != 0) {
        ActionType type = ACTION_NONE;
        switch(actionstate) {
            case 1: type = ACTION_FRONT; break;
            case 2: type = ACTION_LEFT; break;
            case 3: type = ACTION_RIGHT; break;
            case 4: type = ACTION_BACK; break;
            case 5: type = ACTION_TOP_LEFT_HAND; break;
            case 6: type = ACTION_TOP_RIGHT_HAND; break;
            case 7: type = ACTION_LIE; break;
            case 8: type = ACTION_SITDOWN; break;
            case 10: type = ACTION_SLEEP; break;
            case 9: emojiState = random(0, 7); break;
        }
        if (type != ACTION_NONE) actionSequencer.startAction(type);
        actionstate = 0; 
    }

    static int prevEmojiState = -1;
    if (emojiState != prevEmojiState) {
        if (emojiState == 7) { // Display cached weather
            displayManager.showWeather(cachedWeatherData.temperature, cachedWeatherData.humidity, cachedWeatherData.weather);
        } else if (emojiState == 8) { // Display cached time
            displayManager.showTime(cachedFormattedTime);
        } else {
            displayManager.showEmotion(emojiState);
        }
        prevEmojiState = emojiState;
    }
}