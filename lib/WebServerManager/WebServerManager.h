#ifndef WEBSERVERMANAGER_H
#define WEBSERVERMANAGER_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "servofoot.h"
#include "oledDisplay.h"

// Forward declaration
class WebServerManager;

// Define a function pointer type for action handlers
using ActionHandler = void (*)(int);

class WebServerManager {
public:
    WebServerManager(int& actionstate, int& emojiState, int& speed, bool& freestate, String& useruid, String& cityname, String& weatherapi, float& batteryVoltage, int& batteryPercentage);
    void begin();
    void setActionHandler(ActionHandler handler);

private:
    void handleFront(AsyncWebServerRequest *request);
    void handleBack(AsyncWebServerRequest *request);
    void handleLeft(AsyncWebServerRequest *request);
    void handleRight(AsyncWebServerRequest *request);
    void handleTopLeftHand(AsyncWebServerRequest *request);
    void handleTopRightHand(AsyncWebServerRequest *request);
    void handleSitDown(AsyncWebServerRequest *request);
    void handleLie(AsyncWebServerRequest *request);
    void handleSleep(AsyncWebServerRequest *request);
    void handleFree(AsyncWebServerRequest *request);
    void handleOffFree(AsyncWebServerRequest *request);
    void handleHiState(AsyncWebServerRequest *request);
    void handleAngryState(AsyncWebServerRequest *request);
    void handleEdaState(AsyncWebServerRequest *request);
    void handleErrorState(AsyncWebServerRequest *request);
    void handleDoWhatState(AsyncWebServerRequest *request);
    void handleLoveState(AsyncWebServerRequest *request);
    void handleSickState(AsyncWebServerRequest *request);
    void handleYunState(AsyncWebServerRequest *request);
    void handleTime(AsyncWebServerRequest *request);
    void handleWeather(AsyncWebServerRequest *request);
    void handleBatteryVoltage(AsyncWebServerRequest *request);
    void handleBatteryPercentage(AsyncWebServerRequest *request);
    void handleSpeed(AsyncWebServerRequest *request);
    void handleSpeedUp(AsyncWebServerRequest *request);
    void handleSpeedDown(AsyncWebServerRequest *request);
    void handleConnect(AsyncWebServerRequest *request);
    void handleRoot(AsyncWebServerRequest *request);
    void handleControl(AsyncWebServerRequest *request);
    void handleSetting(AsyncWebServerRequest *request);
    void handleNotFound(AsyncWebServerRequest *request);


    AsyncWebServer _server;
    int& _actionstate;
    int& _emojiState;
    int& _speed;
    bool& _freestate;
    String& _useruid;
    String& _cityname;
    String& _weatherapi;
    float& _batteryVoltage;
    int& _batteryPercentage;
    ActionHandler _actionHandler;
};

#endif // WEBSERVERMANAGER_H
