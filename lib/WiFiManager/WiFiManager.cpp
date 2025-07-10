#include "WiFiManager.h"
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <FS.h>

WiFiManager::WiFiManager(const char* ssidFile) : _ssidFile(ssidFile) {}

bool WiFiManager::loadConfig() {
    if (!SPIFFS.begin()) {
        Serial.println("SPIFFS initialization failed!");
        return false;
    }

    fs::File file = SPIFFS.open(_ssidFile, "r");
    if (!file) {
        Serial.println("Failed to open config file for reading.");
        return false;
    }

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, file);
    file.close();

    if (error) {
        Serial.println("Failed to parse config file.");
        return false;
    }

    String ssid = doc["ssid"];
    String pass = doc["pass"];
    _uid = doc["uid"].as<String>();
    _city = doc["city"].as<String>();
    _apiKey = doc["api"].as<String>();

    WiFi.begin(ssid.c_str(), pass.c_str());

    Serial.print("Connecting to WiFi...");
    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 5000) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("\nConnection Failed!");
        return false;
    }

    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    return true;
}

void WiFiManager::setupAP(const char* ssid, const char* password) {
    WiFi.softAP(ssid, password);
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

String WiFiManager::getUID() {
    return _uid;
}

String WiFiManager::getCity() {
    return _city;
}

String WiFiManager::getAPIKey() {
    return _apiKey;
}
