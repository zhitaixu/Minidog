
#ifndef CONFIG_H
#define CONFIG_H

// Pin Definitions
#define BUTTON_PIN 2
#define PIXEL_PIN 13
#define ENGINE1_PIN 14
#define ENGINE2_PIN 16
#define ENGINE3_PIN 12
#define ENGINE4_PIN 15

// NeoPixel Settings
#define PIXEL_COUNT 6

// WiFi Settings
#define AP_SSID "EDA-Robot"
#define AP_PASSWORD ""
#define SSID_FILE "/ssid.json"

// NTP Settings
#define NTP_SERVER "ntp1.aliyun.com"
#define NTP_TIME_OFFSET (8 * 3600)
#define NTP_UPDATE_INTERVAL 60000

// Other settings
#define INITIAL_SPEED 300

#endif // CONFIG_H
