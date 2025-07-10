
#include "WeatherService.h"
#include <ESP8266WiFi.h>

WeatherService::WeatherService(const String& apiKey, const String& city) 
    : _apiKey(apiKey), _city(city) {}

void WeatherService::reconfigure(const String& apiKey, const String& city) {
    _apiKey = apiKey;
    _city = city;
}

bool WeatherService::fetchWeather(WeatherData& data) {
    if (WiFi.status() != WL_CONNECTED) {
        return false;
    }

    WiFiClient client;
    HTTPClient http;
    String url = String(_apiHost) + _apiKey + "&location=" + _city + "&language=zh-Hans&unit=c&start=0&days=1";

    if (http.begin(client, url)) {
        int httpCode = http.GET();
        if (httpCode > 0) {
            String payload = http.getString();
            http.end();

            DynamicJsonDocument doc(1024);
            DeserializationError error = deserializeJson(doc, payload);

            if (error) {
                Serial.println("Failed to parse weather JSON");
                return false;
            }

            data.temperature = doc["results"][0]["daily"][0]["high"].as<String>();
            data.humidity = doc["results"][0]["daily"][0]["humidity"].as<String>();
            data.weather = doc["results"][0]["daily"][0]["text_day"].as<String>();
            return true;
        }
        http.end();
    }
    return false;
}
