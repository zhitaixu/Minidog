
#ifndef WEATHERSERVICE_H
#define WEATHERSERVICE_H

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

struct WeatherData {
    String temperature;
    String humidity;
    String weather;
};

class WeatherService {
public:
    WeatherService(const String& apiKey, const String& city);
    void reconfigure(const String& apiKey, const String& city);
    bool fetchWeather(WeatherData& data);

private:
    String _apiKey;
    String _city;
    const char* _apiHost = "http://api.seniverse.com/v3/weather/daily.json?key=";
};

#endif // WEATHERSERVICE_H
