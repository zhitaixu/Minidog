
#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <FS.h>

class WiFiManager {
public:
    WiFiManager(const char* ssidFile);
    bool loadConfig();
    void setupAP(const char* ssid, const char* password);
    bool isConnected();
    String getUID();
    String getCity();
    String getAPIKey();

private:
    const char* _ssidFile;
    String _uid;
    String _city;
    String _apiKey;
};

#endif // WIFIMANAGER_H
