#include "WebServerManager.h"
#include <FS.h>

WebServerManager::WebServerManager(int& actionstate, int& emojiState, int& speed, bool& freestate, String& useruid, String& cityname, String& weatherapi, float& batteryVoltage, int& batteryPercentage)
    : _server(80), _actionstate(actionstate), _emojiState(emojiState), _speed(speed), _freestate(freestate), _useruid(useruid), _cityname(cityname), _weatherapi(weatherapi), _batteryVoltage(batteryVoltage), _batteryPercentage(batteryPercentage), _actionHandler(nullptr) {}

void WebServerManager::begin() {
    _server.on("/front", HTTP_GET, std::bind(&WebServerManager::handleFront, this, std::placeholders::_1));
    _server.on("/back", HTTP_GET, std::bind(&WebServerManager::handleBack, this, std::placeholders::_1));
    _server.on("/left", HTTP_GET, std::bind(&WebServerManager::handleLeft, this, std::placeholders::_1));
    _server.on("/right", HTTP_GET, std::bind(&WebServerManager::handleRight, this, std::placeholders::_1));
    _server.on("/toplefthand", HTTP_GET, std::bind(&WebServerManager::handleTopLeftHand, this, std::placeholders::_1));
    _server.on("/toprighthand", HTTP_GET, std::bind(&WebServerManager::handleTopRightHand, this, std::placeholders::_1));
    _server.on("/sitdown", HTTP_GET, std::bind(&WebServerManager::handleSitDown, this, std::placeholders::_1));
    _server.on("/lie", HTTP_GET, std::bind(&WebServerManager::handleLie, this, std::placeholders::_1));
    _server.on("/sleep", HTTP_GET, std::bind(&WebServerManager::handleSleep, this, std::placeholders::_1));
    _server.on("/free", HTTP_GET, std::bind(&WebServerManager::handleFree, this, std::placeholders::_1));
    _server.on("/offfree", HTTP_GET, std::bind(&WebServerManager::handleOffFree, this, std::placeholders::_1));
    _server.on("/histate", HTTP_GET, std::bind(&WebServerManager::handleHiState, this, std::placeholders::_1));
    _server.on("/angrystate", HTTP_GET, std::bind(&WebServerManager::handleAngryState, this, std::placeholders::_1));
    _server.on("/edastate", HTTP_GET, std::bind(&WebServerManager::handleEdaState, this, std::placeholders::_1));
    _server.on("/errorstate", HTTP_GET, std::bind(&WebServerManager::handleErrorState, this, std::placeholders::_1));
    _server.on("/dowhatstate", HTTP_GET, std::bind(&WebServerManager::handleDoWhatState, this, std::placeholders::_1));
    _server.on("/lovestate", HTTP_GET, std::bind(&WebServerManager::handleLoveState, this, std::placeholders::_1));
    _server.on("/sickstate", HTTP_GET, std::bind(&WebServerManager::handleSickState, this, std::placeholders::_1));
    _server.on("/yunstate", HTTP_GET, std::bind(&WebServerManager::handleYunState, this, std::placeholders::_1));
    _server.on("/time", HTTP_GET, std::bind(&WebServerManager::handleTime, this, std::placeholders::_1));
    _server.on("/weather", HTTP_GET, std::bind(&WebServerManager::handleWeather, this, std::placeholders::_1));
    _server.on("/batteryVoltage", HTTP_GET, std::bind(&WebServerManager::handleBatteryVoltage, this, std::placeholders::_1));
    _server.on("/batteryPercentage", HTTP_GET, std::bind(&WebServerManager::handleBatteryPercentage, this, std::placeholders::_1));
    _server.on("/speed", HTTP_GET, std::bind(&WebServerManager::handleSpeed, this, std::placeholders::_1));
    _server.on("/speedup", HTTP_GET, std::bind(&WebServerManager::handleSpeedUp, this, std::placeholders::_1));
    _server.on("/speeddown", HTTP_GET, std::bind(&WebServerManager::handleSpeedDown, this, std::placeholders::_1));
    _server.on("/connect", HTTP_POST, std::bind(&WebServerManager::handleConnect, this, std::placeholders::_1));
    _server.on("/", HTTP_GET, std::bind(&WebServerManager::handleRoot, this, std::placeholders::_1));
    _server.on("/control.html", HTTP_GET, std::bind(&WebServerManager::handleControl, this, std::placeholders::_1));
    _server.on("/setting.html", HTTP_GET, std::bind(&WebServerManager::handleSetting, this, std::placeholders::_1));
    _server.onNotFound(std::bind(&WebServerManager::handleNotFound, this, std::placeholders::_1));

    _server.begin();
}

void WebServerManager::setActionHandler(ActionHandler handler) {
    _actionHandler = handler;
}

void WebServerManager::handleFront(AsyncWebServerRequest *request) {
    _actionstate = 1;
    if (_actionHandler) _actionHandler(_actionstate);
    request->send(200, "text/plain", "Front function started");
}

void WebServerManager::handleBack(AsyncWebServerRequest *request) {
    _actionstate = 4;
    if (_actionHandler) _actionHandler(_actionstate);
    request->send(200, "text/plain", "Back function started");
}

void WebServerManager::handleLeft(AsyncWebServerRequest *request) {
    _actionstate = 2;
    if (_actionHandler) _actionHandler(_actionstate);
    request->send(200, "text/plain", "Left function started");
}

void WebServerManager::handleRight(AsyncWebServerRequest *request) {
    _actionstate = 3;
    if (_actionHandler) _actionHandler(_actionstate);
    request->send(200, "text/plain", "Right function started");
}

void WebServerManager::handleTopLeftHand(AsyncWebServerRequest *request) {
    _actionstate = 5;
    if (_actionHandler) _actionHandler(_actionstate);
    request->send(200, "text/plain", "Top-left hand function started");
}

void WebServerManager::handleTopRightHand(AsyncWebServerRequest *request) {
    _actionstate = 6;
    if (_actionHandler) _actionHandler(_actionstate);
    request->send(200, "text/plain", "Top-right hand function started");
}

void WebServerManager::handleSitDown(AsyncWebServerRequest *request) {
    _actionstate = 8;
    if (_actionHandler) _actionHandler(_actionstate);
    request->send(200, "text/plain", "Sit down function started");
}

void WebServerManager::handleLie(AsyncWebServerRequest *request) {
    _actionstate = 7;
    if (_actionHandler) _actionHandler(_actionstate);
    request->send(200, "text/plain", "Lie function started");
}

void WebServerManager::handleSleep(AsyncWebServerRequest *request) {
    _actionstate = 10;
    if (_actionHandler) _actionHandler(_actionstate);
    request->send(200, "text/plain", "Sleep function started");
}

void WebServerManager::handleFree(AsyncWebServerRequest *request) {
    _freestate = true;
    request->send(200, "text/plain", "Free mode started");
}

void WebServerManager::handleOffFree(AsyncWebServerRequest *request) {
    _freestate = false;
    request->send(200, "text/plain", "Free mode stopped");
}

void WebServerManager::handleHiState(AsyncWebServerRequest *request) {
    _emojiState = 0;
    request->send(200, "text/plain", "Hi state set");
}

void WebServerManager::handleAngryState(AsyncWebServerRequest *request) {
    _emojiState = 1;
    request->send(200, "text/plain", "Angry state set");
}

void WebServerManager::handleEdaState(AsyncWebServerRequest *request) {
    _emojiState = 9;
    request->send(200, "text/plain", "Eda state set");
}

void WebServerManager::handleErrorState(AsyncWebServerRequest *request) {
    _emojiState = 2;
    request->send(200, "text/plain", "Error state set");
}

void WebServerManager::handleDoWhatState(AsyncWebServerRequest *request) {
    _emojiState = 3;
    request->send(200, "text/plain", "'Do what' state set");
}

void WebServerManager::handleLoveState(AsyncWebServerRequest *request) {
    _emojiState = 4;
    request->send(200, "text/plain", "Love state set");
}

void WebServerManager::handleSickState(AsyncWebServerRequest *request) {
    _emojiState = 5;
    request->send(200, "text/plain", "Sick state set");
}

void WebServerManager::handleYunState(AsyncWebServerRequest *request) {
    _emojiState = 6;
    request->send(200, "text/plain", "Yun state set");
}

void WebServerManager::handleTime(AsyncWebServerRequest *request) {
    _emojiState = 8;
    request->send(200, "text/plain", "Time state set");
}

void WebServerManager::handleWeather(AsyncWebServerRequest *request) {
    _emojiState = 7;
    request->send(200, "text/plain", "Weather state set");
}

void WebServerManager::handleBatteryVoltage(AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(_batteryVoltage));
}

void WebServerManager::handleBatteryPercentage(AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(_batteryPercentage));
}

void WebServerManager::handleSpeed(AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(_speed));
}

void WebServerManager::handleSpeedUp(AsyncWebServerRequest *request) {
    _speed++;
    request->send(200, "text/plain", "Speed increased");
}

void WebServerManager::handleSpeedDown(AsyncWebServerRequest *request) {
    _speed--;
    request->send(200, "text/plain", "Speed decreased");
}

void WebServerManager::handleConnect(AsyncWebServerRequest *request) {
    String ssid = request->getParam("ssid", true)->value();
    String pass = request->getParam("pass", true)->value();
    String uid = request->getParam("uid", true)->value();
    String city = request->getParam("city", true)->value();
    String api = request->getParam("api", true)->value();

    DynamicJsonDocument doc(1024);
    doc["ssid"] = ssid;
    doc["pass"] = pass;
    doc["uid"] = uid;
    doc["city"] = city;
    doc["api"] = api;

    fs::File file = SPIFFS.open("/ssid.json", "w");
    if (file) {
        serializeJson(doc, file);
        file.close();
    }

    _useruid = uid;
    _cityname = city;
    _weatherapi = api;

    WiFi.begin(ssid.c_str(), pass.c_str());
    request->send(200, "text/html", "<h1>Connecting...</h1>");
}

void WebServerManager::handleRoot(AsyncWebServerRequest *request) {
    if (SPIFFS.exists("/index.html")) {
        request->send(SPIFFS, "/index.html", "text/html");
    } else {
        request->send(404, "text/plain", "File Not Found");
    }
}

void WebServerManager::handleControl(AsyncWebServerRequest *request) {
    if (SPIFFS.exists("/control.html")) {
        request->send(SPIFFS, "/control.html", "text/html");
    } else {
        request->send(404, "text/plain", "File Not Found");
    }
}

void WebServerManager::handleSetting(AsyncWebServerRequest *request) {
    if (SPIFFS.exists("/setting.html")) {
        request->send(SPIFFS, "/setting.html", "text/html");
    } else {
        request->send(404, "text/plain", "File Not Found");
    }
}

void WebServerManager::handleNotFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
