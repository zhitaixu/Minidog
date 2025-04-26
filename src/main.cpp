// 导入头文件
#include <Arduino.h>
#include <Servo.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include "image.cpp"
#include "ws2812b.h"
#include "button.h"

#define BUTTON_PIN 2 // 现在在main.cpp定义了引脚

#define PIXEL_PIN    13  // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 6  // Number of NeoPixels



// 定义
// 分压器比例（输入电压到 ADC 电压的比例）
const float voltageDividerRatio = 8.4; // 分压比（8.4倍缩小）
// 电压范围（电池电压）
const float minVoltage = 6.4; // 电压为0%时
const float maxVoltage = 8.4; // 电压为100%时
// 采样次数
const int numSamples = 10;
float batteryVoltage = 0; // 计算电池电压
int batteryPercentage = 0;


Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;


U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/5, /* data=*/4); // ESP32 Thing, HW I2C with pin remapping
// 设置WiFi热点名称和密码
const char *ssid = "EDA-Robot";
const char *password = ""; // 无密码
AsyncWebServer server(80);
// random(minValue, maxValue)
//  微调参数值，舵机1
WiFiUDP ntpUDP;
const char *weatherAPI = "http://api.seniverse.com/v3/weather/daily.json?key=";
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com", 8 * 3600, 60000);
String temperature = "";
String humidity = "";
String weather = "";
String useruid = "";
String cityname = "";
String weatherapi = "";




int engine1 = 14;                 // 舵机引脚
// int engine1offsetleftpwm = -93;   // 舵机左转补偿
// int engine1offsetrightpwm = -87;  // 舵机左转补偿-40
int engine2 = 16;                 // 舵机引脚
// int engine2offsetleftpwm = -120;  // 舵机左转补偿
// int engine2offsetrightpwm = -122; // 舵机左转补偿-60
int engine3 = 12;                 // 舵机引脚
// int engine3offsetleftpwm = -3;    // 舵机左转补偿
// int engine3offsetrightpwm = -57;  // 舵机左转补偿
int engine4 = 15;                 // 舵机引脚
// int engine4offsetleftpwm = -78;   // 舵机左转补偿
// int engine4offsetrightpwm = -109; // 舵机左转补偿-71
int speed = 300;                  // 舵机转速




int runtime = 100;                // 运动延时**预留变量，用于控制动作连贯性，如果你不知道这是什么不建议修改**
static bool initweather = false;  // 天气初始化
bool freestate = false;
// 定义一个标志来检查是否需要执行动作
int prevEmojiState = -1; // 用于跟踪之前的 emojiState
int actionstate = 0;
int emojiState = 0; // 表情状态
const char *ssidFile = "/ssid.json";




void handleWiFiConfig()
{
    // 启动服务器

    server.on("/front", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        actionstate = 1;  // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/back", HTTP_GET, [](AsyncWebServerRequest *request)
              {
       actionstate = 4;   // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/left", HTTP_GET, [](AsyncWebServerRequest *request)
              {
       actionstate = 2;  // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/right", HTTP_GET, [](AsyncWebServerRequest *request)
              {
       actionstate = 3;  // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/toplefthand", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        actionstate = 5;   // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/toprighthand", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        actionstate = 6;  // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/sitdown", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        actionstate = 8;  // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/lie", HTTP_GET, [](AsyncWebServerRequest *request)
              {
      actionstate = 7; 
        request->send(200, "text/plain", "Front function started"); });
         server.on("/sleep", HTTP_GET, [](AsyncWebServerRequest *request)
              {
      actionstate = 10; 
        request->send(200, "text/plain", "Front function started"); });
    // server.on("/dance", HTTP_GET, [](AsyncWebServerRequest *request)
    //           {
    //     actionstate = 7;  // 设置标志，执行舵机动作
    //     request->send(200, "text/plain", "Front function started"); });
    server.on("/free", HTTP_GET, [](AsyncWebServerRequest *request)
              {
      freestate=true;
        request->send(200, "text/plain", "Front function started"); });
    server.on("/offfree", HTTP_GET, [](AsyncWebServerRequest *request)
              {
      freestate=false;
        request->send(200, "text/plain", "Front function started"); });
    server.on("/histate", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        emojiState = 0;  // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/angrystate", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        emojiState = 1;   // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/edastate", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        emojiState = 9;   // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });

    server.on("/errorstate", HTTP_GET, [](AsyncWebServerRequest *request)
              {
       emojiState = 2;  // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/batteryVoltage", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(batteryVoltage)); });
    server.on("/batteryPercentage", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(batteryPercentage)); });
    server.on("/speed", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(speed)); });
    server.on("/speedup", HTTP_GET, [](AsyncWebServerRequest *request)
              {
       speed++;  // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/speeddown", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    speed--;
        request->send(200, "text/plain", "Front function started"); });
    server.on("/speedup", HTTP_GET, [](AsyncWebServerRequest *request)
              {
       speed++;  // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/speeddown", HTTP_GET, [](AsyncWebServerRequest *request)
              {
       speed--;
        request->send(200, "text/plain", "Front function started"); });
    server.on("/dowhatstate", HTTP_GET, [](AsyncWebServerRequest *request)
              {
       emojiState = 3;  // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/lovestate", HTTP_GET, [](AsyncWebServerRequest *request)
              {
       emojiState = 4;  // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/sickstate", HTTP_GET, [](AsyncWebServerRequest *request)
              {
       emojiState = 5;  // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });
    server.on("/yunstate", HTTP_GET, [](AsyncWebServerRequest *request)
              {
       emojiState = 6; 
        request->send(200, "text/plain", "Front function started"); });
    server.on("/time", HTTP_GET, [](AsyncWebServerRequest *request)
              {
       emojiState = 8; 
        request->send(200, "text/plain", "Front function started"); });
    server.on("/weather", HTTP_GET, [](AsyncWebServerRequest *request)
              {
       emojiState = 7;  // 设置标志，执行舵机动作
        request->send(200, "text/plain", "Front function started"); });

    server.on("/connect", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        // 获取POST参数：ssid、pass、uid、city、api
        String ssid = request->getParam("ssid", true)->value();
        String pass = request->getParam("pass", true)->value();
        String uid = request->getParam("uid", true)->value();
        String city = request->getParam("city", true)->value();
        String api = request->getParam("api", true)->value();

        // 打印接收到的参数
        Serial.println(ssid);
        Serial.println(pass);

        // 保存WiFi信息到JSON文件
        DynamicJsonDocument doc(1024);
        doc["ssid"] = ssid;
        doc["pass"] = pass;
        doc["uid"] = uid;
        doc["city"] = city;
        doc["api"] = api;
        fs::File file = SPIFFS.open(ssidFile, "w");  // 打开文件进行写入
        if (file) {
            serializeJson(doc, file);  // 将JSON内容写入文件
            file.close();  // 关闭文件
        }

        // 更新全局变量
        useruid = uid;
        cityname = city;
        weatherapi = api;

        // 开始连接WiFi
        WiFi.begin(ssid.c_str(), pass.c_str());
        // 发送HTML响应，告知用户正在连接
        request->send(200, "text/html", "<h1>Connecting...</h1>"); });

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        // 检查SPIFFS文件系统中是否存在index.html文件
        if (SPIFFS.exists("/index.html")) {
            fs::File file = SPIFFS.open("/index.html", "r");  // 打开index.html文件
            if (file) {
                size_t fileSize = file.size();  // 获取文件大小
                String fileContent;

                // 逐字节读取文件内容
                while (file.available()) {
                    fileContent += (char)file.read();
                }
                file.close();  // 关闭文件

                // 返回HTML内容
                request->send(200, "text/html", fileContent);
                return;
            }
        }
        // 如果文件不存在，返回404错误
        request->send(404, "text/plain", "File Not Found"); });
    server.on("/control.html", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        // 检查SPIFFS文件系统中是否存在index.html文件
        if (SPIFFS.exists("/control.html")) {
            fs::File file = SPIFFS.open("/control.html", "r");  // 打开index.html文件
            if (file) {
                size_t fileSize = file.size();  // 获取文件大小
                String fileContent;

                // 逐字节读取文件内容
                while (file.available()) {
                    fileContent += (char)file.read();
                }
                file.close();  // 关闭文件

                // 返回HTML内容
                request->send(200, "text/html", fileContent);
                return;
            }
        }
        // 如果文件不存在，返回404错误
        request->send(404, "text/plain", "File Not Found"); });
    server.on("/engine.html", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        // 检查SPIFFS文件系统中是否存在index.html文件
        if (SPIFFS.exists("/engine.html")) {
            fs::File file = SPIFFS.open("/engine.html", "r");  // 打开index.html文件
            if (file) {
                size_t fileSize = file.size();  // 获取文件大小
                String fileContent;

                // 逐字节读取文件内容
                while (file.available()) {
                    fileContent += (char)file.read();
                }
                file.close();  // 关闭文件

                // 返回HTML内容
                request->send(200, "text/html", fileContent);
                return;
            }
        }
        // 如果文件不存在，返回404错误
        request->send(404, "text/plain", "File Not Found"); });
    server.on("/setting.html", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        // 检查SPIFFS文件系统中是否存在index.html文件
        if (SPIFFS.exists("/setting.html")) {
            fs::File file = SPIFFS.open("/setting.html", "r");  // 打开index.html文件
            if (file) {
                size_t fileSize = file.size();  // 获取文件大小
                String fileContent;

                // 逐字节读取文件内容
                while (file.available()) {
                    fileContent += (char)file.read();
                }
                file.close();  // 关闭文件

                // 返回HTML内容
                request->send(200, "text/html", fileContent);
                return;
            }
        }
        // 如果文件不存在，返回404错误
        request->send(404, "text/plain", "File Not Found"); });
    // 启动服务器
    server.begin();
};
void loadWiFiConfig()
{
    if (SPIFFS.begin())
    {
        fs::File file = SPIFFS.open(ssidFile, "r");
        if (file)
        {
            DynamicJsonDocument doc(1024);
            DeserializationError error = deserializeJson(doc, file);
            if (!error)
            {
                String ssid = doc["ssid"];
                String pass = doc["pass"];
                String uid = doc["uid"];
                String city = doc["city"];
                String api = doc["api"];
                useruid = uid;
                cityname = city;
                weatherapi = api;
                WiFi.begin(ssid.c_str(), pass.c_str());
                // 尝试连接WiFi，最多等待10秒
                unsigned long startAttemptTime = millis();
                while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 5000)
                {
                    delay(500);
                }
                // 如果连接失败，打印状态
                if (WiFi.status() != WL_CONNECTED)
                {
                    Serial.println("WiFi connection failed, starting captive portal...");
                    handleWiFiConfig(); // 启动强制门户
                }
                else
                {
                    Serial.println("WiFi connected");
                    timeClient.begin();
                }
            }
            file.close();
        }
    }
}
void fetchWeather()
{ // 天气捕捉
    if (initweather == false)
    {
        //  mylcd.fillScreen(TFT_BLACK);
        if (WiFi.status() == WL_CONNECTED)
        {
            WiFiClient client;
            HTTPClient http;
            if (http.begin(client, weatherAPI + weatherapi + "&location=" + cityname + "&language=zh-Hans&unit=c&start=0&days=1"))
            {
                int httpCode = http.GET();
                if (httpCode > 0)
                {
                    String payload = http.getString();
                    Serial.println("JSON Response:");
                    Serial.println(payload);
                    DynamicJsonDocument doc(1024);
                    deserializeJson(doc, payload);
                    String temperature2 = doc["results"][0]["daily"][0]["high"];
                    String humidity2 = doc["results"][0]["daily"][0]["humidity"];
                    String weathe2r = doc["results"][0]["daily"][0]["text_day"];
                    temperature = temperature2;
                    humidity = humidity2;
                    weather = weathe2r;
                    initweather = true;
                    Serial.print("Data received: ");
                    Serial.println(temperature);
                    Serial.println(humidity);
                    Serial.println(weather);
                }
                else
                {
                    Serial.printf("HTTP GET request failed, error: %s\n", http.errorToString(httpCode).c_str());
                }
                http.end();
            }
            else
            {
                Serial.println("Failed to connect to server");
            }
            //  mylcd.fillScreen(TFT_BLACK);
        }
    }
    if (weather == "阴" || weather == "多云")
    {
        do
        {
            u8g2.setFont(u8g2_font_ncenB08_tr);
            u8g2.drawXBMP(0, 0, 64, 64, cloud);
            u8g2.drawStr(64, 20, "Temp");
            String temperatureString = String(temperature) + " C";
            u8g2.drawStr(64, 30, temperatureString.c_str());
            u8g2.drawStr(64, 50, "Humidity");
            String humidityString = String(humidity) + " %";
            u8g2.drawStr(64, 60, humidityString.c_str());
        } while (u8g2.nextPage());
        // mylcd.pushImage(mylcd.width() / 2-(99/2), 10, 99, 99,cloud);
    }
    else if (weather == "小雨" || weather == "大雨" || weather == "暴雨" || weather == "雨")
    {
        do
        {
            u8g2.setFont(u8g2_font_ncenB08_tr);
            u8g2.drawXBMP(0, 0, 64, 64, rain);
            u8g2.drawStr(64, 20, "Temp");
            String temperatureString = String(temperature) + " %";
            u8g2.drawStr(64, 30, temperatureString.c_str());
            u8g2.drawStr(64, 50, "Humidity");
            String humidityString = String(humidity) + " %";
            u8g2.drawStr(64, 60, humidityString.c_str());
        } while (u8g2.nextPage());
    }
    else if (weather == "晴")
    {
        do
        {
            u8g2.setFont(u8g2_font_ncenB08_tr);
            u8g2.drawStr(64, 20, "Temp");
            u8g2.drawXBMP(0, 0, 64, 64, sun);
            String temperatureString = String(temperature) + " %";
            u8g2.drawStr(64, 30, temperatureString.c_str());
            u8g2.drawStr(64, 50, "Humidity");
            String humidityString = String(humidity) + " %";
            u8g2.drawStr(64, 60, humidityString.c_str());
        } while (u8g2.nextPage());
    }
}



// 对 ADC 数据多次采样并计算平均值
float getAverageAdcVoltage()
{
    long totalAdcValue = 0;

    // 多次采样
    for (int i = 0; i < numSamples; i++)
    {
        totalAdcValue += analogRead(A0); // 读取 ADC 数据
        delay(10);                       // 每次采样间隔 10ms
    }

    // 计算平均 ADC 值
    float averageAdcValue = totalAdcValue / (float)numSamples;

    // 将 ADC 值转换为电压
    return (averageAdcValue / 1023.0) * 1.0; // ESP8266 的参考电压为 1.0V
}

// 计算电池电量百分比的函数
int mapBatteryPercentage(float voltage)
{
    if (voltage <= minVoltage)
        return 0; // 小于等于最小电压时，电量为 0%
    if (voltage >= maxVoltage)
        return 100; // 大于等于最大电压时，电量为 100%

    // 根据线性比例计算电量百分比
    return (int)((voltage - minVoltage) / (maxVoltage - minVoltage) * 100);
}








void front()
{
    servo2.write(140); // 旋转到 90 度
    servo3.write(40);  // 旋转到 90 度
    delay(100);
    servo1.write(40);  // 旋转到 90 度
    servo4.write(140); // 旋转到 90 度
    delay(100);
    servo2.write(90); // 旋转到 90 度
    servo3.write(90); // 旋转到 90 度
    delay(100);
    servo1.write(90); // 旋转到 90 度
    servo4.write(90); // 旋转到 90 度
    delay(100);
    servo1.write(140); // 旋转到 90 度
    servo4.write(40);  // 旋转到 90 度
    delay(100);
    servo2.write(40);  // 旋转到 90 度
    servo3.write(140); // 旋转到 90 度
    delay(100);
    servo1.write(90); // 旋转到 90 度
    servo4.write(90); // 旋转到 90 度
    delay(100);
    servo2.write(90); // 旋转到 90 度
    servo3.write(90); // 旋转到 90 度

    // //+30C 2/3
    // servo2.writeMicroseconds(1500 + speed + engine2offsetleftpwm);
    // servo3.writeMicroseconds(1500 - speed - engine3offsetleftpwm);
    // delay(500-runtime);
    // servo2.writeMicroseconds(1500);
    // servo3.writeMicroseconds(1500);
    // //-30C 1/4
    // servo1.writeMicroseconds(1500 - speed - engine1offsetrightpwm);
    // servo4.writeMicroseconds(1500 + speed + engine4offsetrightpwm);
    // delay(500-runtime);
    // servo1.writeMicroseconds(1500);
    // servo4.writeMicroseconds(1500);
    // // 0C 2/3
    // servo2.writeMicroseconds(1500 - speed - engine2offsetrightpwm);
    // servo3.writeMicroseconds(1500 + speed + engine3offsetrightpwm);
    // delay(500-runtime);
    // servo2.writeMicroseconds(1500);
    // servo3.writeMicroseconds(1500);
    // // 0C 1/4
    // servo1.writeMicroseconds(1500 + speed + engine1offsetleftpwm);
    // servo4.writeMicroseconds(1500 - speed - engine4offsetleftpwm);
    // delay(500-runtime);
    // servo1.writeMicroseconds(1500);
    // servo4.writeMicroseconds(1500);
    // //+30C 1/4
    // servo1.writeMicroseconds(1500 + speed + engine1offsetleftpwm);
    // servo4.writeMicroseconds(1500 - speed - engine4offsetleftpwm);
    // delay(500-runtime);
    // servo1.writeMicroseconds(1500);
    // servo4.writeMicroseconds(1500);
    // //-30C 2/3
    // servo2.writeMicroseconds(1500 - speed - engine2offsetrightpwm);
    // servo3.writeMicroseconds(1500 + speed + engine3offsetrightpwm);
    // delay(500-runtime);
    // servo2.writeMicroseconds(1500);
    // servo3.writeMicroseconds(1500);
    // // 0C 1/4
    // servo1.writeMicroseconds(1500 - speed - engine1offsetrightpwm);
    // servo4.writeMicroseconds(1500 + speed + engine4offsetrightpwm);
    // delay(500-runtime);
    // servo1.writeMicroseconds(1500);
    // servo4.writeMicroseconds(1500);
    // // 0C 2/3
    // servo2.writeMicroseconds(1500 + speed + engine2offsetleftpwm);
    // servo3.writeMicroseconds(1500 - speed - engine3offsetleftpwm);
    // delay(500-runtime);
    // servo2.writeMicroseconds(1500);
    // servo3.writeMicroseconds(1500);
}
void back()
{
    servo3.write(140); // 旋转到 90 度
    servo2.write(40);  // 旋转到 90 度
    delay(100);
    servo4.write(40);  // 旋转到 90 度
    servo1.write(140); // 旋转到 90 度
    delay(100);
    servo3.write(90); // 旋转到 90 度
    servo2.write(90); // 旋转到 90 度
    delay(100);
    servo4.write(90); // 旋转到 90 度
    servo1.write(90); // 旋转到 90 度
    delay(100);
    servo4.write(140); // 旋转到 90 度
    servo1.write(40);  // 旋转到 90 度
    delay(100);
    servo3.write(40);  // 旋转到 90 度
    servo2.write(140); // 旋转到 90 度
    delay(100);
    servo4.write(90); // 旋转到 90 度
    servo1.write(90); // 旋转到 90 度
    delay(100);
    servo3.write(90); // 旋转到 90 度
    servo2.write(90); // 旋转到 90 度

    // //+30C 2/3
    // servo2.writeMicroseconds(1500 - speed - engine2offsetrightpwm);
    // servo3.writeMicroseconds(1500 + speed + engine3offsetrightpwm);
    // delay(500-runtime);
    // servo2.writeMicroseconds(1500);
    // servo3.writeMicroseconds(1500);
    // //-30C 1/4
    // servo1.writeMicroseconds(1500 + speed + engine1offsetleftpwm);
    // servo4.writeMicroseconds(1500 - speed - engine4offsetleftpwm);
    // delay(500-runtime);
    // servo1.writeMicroseconds(1500);
    // servo4.writeMicroseconds(1500);
    // // 0C 2/3
    // servo2.writeMicroseconds(1500 + speed + engine2offsetleftpwm);
    // servo3.writeMicroseconds(1500 - speed - engine3offsetleftpwm);
    // delay(500-runtime);
    // servo2.writeMicroseconds(1500);
    // servo3.writeMicroseconds(1500);
    // // 0C 1/4
    // servo1.writeMicroseconds(1500 - speed - engine1offsetrightpwm);
    // servo4.writeMicroseconds(1500 + speed + engine4offsetrightpwm);
    // delay(500-runtime);
    // servo1.writeMicroseconds(1500);
    // servo4.writeMicroseconds(1500);

    // //+30C 1/4
    // servo1.writeMicroseconds(1500 - speed - engine1offsetrightpwm);
    // servo4.writeMicroseconds(1500 + speed + engine4offsetrightpwm);
    // delay(500-runtime);
    // servo1.writeMicroseconds(1500);
    // servo4.writeMicroseconds(1500);
    // //-30C 2/3
    // servo2.writeMicroseconds(1500 + speed + engine2offsetleftpwm);
    // servo3.writeMicroseconds(1500 - speed - engine3offsetleftpwm);
    // delay(500-runtime);
    // servo2.writeMicroseconds(1500);
    // servo3.writeMicroseconds(1500);
    // // 0C 1/4
    // servo1.writeMicroseconds(1500 + speed + engine1offsetleftpwm);
    // servo4.writeMicroseconds(1500 - speed - engine4offsetleftpwm);
    // delay(500-runtime);
    // servo1.writeMicroseconds(1500);
    // servo4.writeMicroseconds(1500);
    // // 0C 2/3
    // servo2.writeMicroseconds(1500 - speed - engine2offsetrightpwm);
    // servo3.writeMicroseconds(1500 + speed + engine3offsetrightpwm);
    // delay(500-runtime);
    // servo2.writeMicroseconds(1500);
    // servo3.writeMicroseconds(1500);
}
void left()
{
    int num = 0;
    while (num < 4)
    {
        servo1.write(100); // 旋转到 90 度
        servo4.write(100); // 旋转到 90 度
        delay(100);
        servo3.write(60); // 旋转到 90 度
        servo2.write(60); // 旋转到 90 度
        delay(100);
        servo1.write(140); // 旋转到 90 度
        servo4.write(140); // 旋转到 90 度
        delay(100);
        servo3.write(40); // 旋转到 90 度
        servo2.write(40); // 旋转到 90 度
        delay(100);
        servo3.write(90); // 旋转到 90 度
        servo2.write(90); // 旋转到 90 度
        servo1.write(90); // 旋转到 90 度
        servo4.write(90); // 旋转到 90 度
        delay(100);
        servo1.write(80); // 旋转到 90 度
        servo4.write(80); // 旋转到 90 度
        delay(100);
        servo3.write(120); // 旋转到 90 度
        servo2.write(120); // 旋转到 90 度
        delay(100);
        servo1.write(90); // 旋转到 90 度
        servo4.write(90); // 旋转到 90 度
        delay(100);
        servo3.write(140); // 旋转到 90 度
        servo2.write(140); // 旋转到 90 度
        delay(100);
        servo3.write(90); // 旋转到 90 度
        servo2.write(90); // 旋转到 90 度

        num++;
    }
    //  +10 1/4
    // servo1.writeMicroseconds(1500 + speed + engine1offsetleftpwm);
    // servo4.writeMicroseconds(1500 + speed + engine4offsetrightpwm);
    // delay(200);
    //  +30
    // servo3.writeMicroseconds(1500 - speed - engine3offsetleftpwm);
    // servo2.writeMicroseconds(1500 - speed - engine2offsetrightpwm);
    // delay(300);
    //  +0 1/4
    // servo1.writeMicroseconds(1500);
    // servo4.writeMicroseconds(1500);
    // +20 2/3
    // delay(200);

    // servo2.writeMicroseconds(1500);
    // servo3.writeMicroseconds(1500);
    // delay(100);
    // //-30
    // servo1.writeMicroseconds(1500 - speed - engine1offsetrightpwm);
    // servo4.writeMicroseconds(1500 - speed - engine4offsetleftpwm);
    // delay(200);
    // servo3.writeMicroseconds(1500 + speed + engine3offsetrightpwm);
    // servo2.writeMicroseconds(1500 + speed + engine2offsetleftpwm);
    // delay(300);
    // servo1.writeMicroseconds(1500);
    // servo4.writeMicroseconds(1500);
    // delay(200);
    // servo2.writeMicroseconds(1500);
    // servo3.writeMicroseconds(1500);
}
void right()
{

    int num = 0;
    while (num < 3)
    {
        servo1.write(80); // 旋转到 90 度
        servo4.write(80); // 旋转到 90 度
        delay(100);
        servo3.write(120); // 旋转到 90 度
        servo2.write(120); // 旋转到 90 度
        delay(100);
        servo1.write(40); // 旋转到 90 度
        servo4.write(40); // 旋转到 90 度
        delay(100);
        servo3.write(140); // 旋转到 90 度
        servo2.write(140); // 旋转到 90 度
        delay(100);
        servo3.write(90); // 旋转到 90 度
        servo2.write(90); // 旋转到 90 度
        servo1.write(90); // 旋转到 90 度
        servo4.write(90); // 旋转到 90 度
        delay(100);
        servo1.write(100); // 旋转到 90 度
        servo4.write(100); // 旋转到 90 度
        delay(100);
        servo3.write(60); // 旋转到 90 度
        servo2.write(60); // 旋转到 90 度
        delay(100);
        servo1.write(90); // 旋转到 90 度
        servo4.write(90); // 旋转到 90 度
        delay(100);
        servo3.write(40); // 旋转到 90 度
        servo2.write(40); // 旋转到 90 度
        delay(100);
        servo3.write(90); // 旋转到 90 度
        servo2.write(90); // 旋转到 90 度

        // //  +30
        // servo1.writeMicroseconds(1500 - speed - engine1offsetrightpwm);
        // servo4.writeMicroseconds(1500 - speed - engine4offsetleftpwm);
        // delay(200);
        // servo3.writeMicroseconds(1500 + speed + engine3offsetrightpwm);
        // servo2.writeMicroseconds(1500 + speed + engine2offsetleftpwm);
        // delay(300);
        // servo1.writeMicroseconds(1500);
        // servo4.writeMicroseconds(1500);
        // delay(200);
        // servo2.writeMicroseconds(1500);
        // servo3.writeMicroseconds(1500);
        // delay(100);
        // //-30
        // servo1.writeMicroseconds(1500 + speed + engine1offsetleftpwm);
        // servo4.writeMicroseconds(1500 + speed + engine4offsetrightpwm);
        // delay(200);
        // servo3.writeMicroseconds(1500 - speed - engine3offsetleftpwm);
        // servo2.writeMicroseconds(1500 - speed - engine2offsetrightpwm);
        // delay(300);
        // servo1.writeMicroseconds(1500);
        // servo4.writeMicroseconds(1500);
        // delay(200);
        // servo2.writeMicroseconds(1500);
        // servo3.writeMicroseconds(1500);
        num++;
    }
}

void sitdown()
{
    servo2.write(140); // 旋转到 90 度
    servo4.write(40);  // 旋转到 90 度
    delay(3000);
    servo2.write(90); // 旋转到 90 度
    servo4.write(90); // 旋转到 90 度

    // servo2.writeMicroseconds(1500 + speed + engine3offsetleftpwm);
    // servo4.writeMicroseconds(1500 - speed - engine3offsetleftpwm);
    // delay(1000);
    // servo2.writeMicroseconds(1500);
    // servo4.writeMicroseconds(1500);
    // delay(3000);
    // servo2.writeMicroseconds(1500 - speed - engine3offsetrightpwm);
    // servo4.writeMicroseconds(1500 + speed + engine3offsetrightpwm);
    // delay(1000);
    // servo2.writeMicroseconds(1500);
    // servo4.writeMicroseconds(1500);
}
void lie()
{
    servo1.write(180); // 旋转到 90 度
    servo3.write(0);   // 旋转到 90 度
    servo2.write(0);   // 旋转到 90 度
    servo4.write(180); // 旋转到 90 度
    delay(3000);
    servo1.write(90); // 旋转到 90 度
    servo3.write(90); // 旋转到 90 度
    servo2.write(90); // 旋转到 90 度
    servo4.write(90); // 旋转到 90 度
                      // servo1.writeMicroseconds(1500 + speed + engine1offsetleftpwm);
                      // servo3.writeMicroseconds(1500 - speed - engine3offsetleftpwm);
                      // servo2.writeMicroseconds(1500 - speed - engine2offsetrightpwm);
                      // servo4.writeMicroseconds(1500 + speed + engine4offsetrightpwm);
                      // delay(1000);
                      // servo1.writeMicroseconds(1500);
                      // servo2.writeMicroseconds(1500);
                      // servo3.writeMicroseconds(1500);
                      // servo4.writeMicroseconds(1500);
                      // delay(3000);
                      // servo1.writeMicroseconds(1500 - speed - engine1offsetrightpwm);
                      // servo3.writeMicroseconds(1500 + speed + engine3offsetrightpwm);
                      // servo2.writeMicroseconds(1500 + speed + engine2offsetleftpwm);
                      // servo4.writeMicroseconds(1500 - speed - engine4offsetleftpwm);
                      // delay(1000);
                      // servo1.writeMicroseconds(1500);
                      // servo2.writeMicroseconds(1500);
                      // servo3.writeMicroseconds(1500);
                      // servo4.writeMicroseconds(1500);
}

void toplefthand()
{
    int num = 0;
    while (num < 3)
    {
        servo3.write(0); // 旋转到 90 度
        delay(100);
        servo3.write(30);
        delay(100);
        // 旋转到 90 度
        // servo3.writeMicroseconds(1500 - speed - engine3offsetleftpwm);
        // delay(1000);
        // servo3.writeMicroseconds(1500);
        // delay(500);
        // servo3.writeMicroseconds(1500 + speed + engine3offsetrightpwm);
        // delay(1000);
        // servo3.writeMicroseconds(1500);
        num++;
    }
    servo3.write(90);
}
void toprighthand()
{

    int num = 0;
    while (num < 3)
    {
        servo1.write(180); // 旋转到 90 度
        delay(100);
        servo1.write(150);
        delay(100);
        // servo1.writeMicroseconds(1500 + speed + engine1offsetleftpwm);
        // delay(1000);
        // servo1.writeMicroseconds(1500);
        // delay(500);
        // servo1.writeMicroseconds(1500 - speed - engine1offsetrightpwm);
        // delay(1000);
        // servo1.writeMicroseconds(1500);
        num++;
    }
    servo1.write(90);
}
void dosleep()
{
    servo1.write(0);                   // 旋转到 90 度
    servo3.write(180);                 // 旋转到 90 度
    servo2.write(180);                 // 旋转到 90 度
    servo4.write(0); 
}


WS2812B ledStrip(PIXEL_COUNT, PIXEL_PIN);


void setup()
{
    ledStrip.begin(); // 初始化 WS2812B LED 灯带


    buttonInit(BUTTON_PIN); // 初始化时传入引脚


    servo1.attach(engine1, 500, 2500); // 引脚 D1，500µs=0度，2500µs=180度
    servo2.attach(engine2, 500, 2500); // 引脚 D1，500µs=0度，2500µs=180度
    servo3.attach(engine3, 500, 2500); // 引脚 D1，500µs=0度，2500µs=180度
    servo4.attach(engine4, 500, 2500); // 引脚 D1，500µs=0度，2500µs=180度
    servo1.write(90);                   // 旋转到 90 度
    servo3.write(90);                 // 旋转到 90 度
    servo2.write(90);                 // 旋转到 90 度
    servo4.write(90);                   // 旋转到 90 度
    // servo1.write(0);                   // 旋转到 90 度
    // servo3.write(180);                 // 旋转到 90 度
    // servo2.write(180);                 // 旋转到 90 度
    // servo4.write(0);                   // 旋转到 90 度
    // servo1.attach(engine1);
    // servo2.attach(engine2);
    // servo3.attach(engine3);
    // servo4.attach(engine4);
    SPIFFS.begin();
    u8g2.begin();
    u8g2.setDisplayRotation(U8G2_R2);
    u8g2.firstPage();
    do
    {
        u8g2.setFont(u8g2_font_ncenB14_tr);
        u8g2.drawXBMP(0, (64 / 2 - 22 / 2), 128, 22, logo);
    } while (u8g2.nextPage());
    // 初始化串口
    Serial.begin(115200);
    // 设置WiFi为热点模式
    WiFi.softAP(ssid, password);
    Serial.println("热点已启动");
    // 访问的IP地址是 ESP8266 的默认IP：192.168.4.1
    Serial.print("访问地址: ");
    Serial.print(WiFi.softAPIP());
    // 加载WiFi配置
    loadWiFiConfig();
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Starting captive portal...");
        handleWiFiConfig();
    }
    else
    {
        handleWiFiConfig();
        Serial.println("WiFi connected");
        timeClient.begin();
        timeClient.update(); // 获取初始时间
    }
    delay(5000);
    u8g2.clearDisplay();
    do
    {
        u8g2.setFont(u8g2_font_ncenB08_tr);
        u8g2.drawXBMP(0, 0, 64, 64, wifi);
        u8g2.drawStr(64, 10, "WIFI_AP");
        u8g2.drawStr(64, 27, "EDA-Robot");
        u8g2.drawStr(64, 43, "192.168.4.1");
        u8g2.drawStr(64, 60, "WIFI CTRL");
    } while (u8g2.nextPage());
    delay(5000);
    u8g2.clearDisplay();
}

void loop()
{
    ledStrip.showRainbow(2);



    // 对 ADC 数据多次采样并求平均
    float adcVoltage = getAverageAdcVoltage();

    // 将采样的 ADC 电压转换为实际电池电压
    batteryVoltage = adcVoltage * voltageDividerRatio; // 计算电池电压

    // 根据电池电压计算电量百分比
    batteryPercentage = mapBatteryPercentage(batteryVoltage);


    if (buttonCheck())
    {
        front();
    }


    if (emojiState != prevEmojiState)
    {
        u8g2.clearDisplay();         // 状态变化时清屏
        prevEmojiState = emojiState; // 更新状态
    }
    if (freestate)
    {
        delay(3000);
        actionstate = random(0, 10);
    }
    // 可以使用switch优化效率
    switch (actionstate)
    {
    case 0 /* constant-expression */:
        /* code */
        break;
    case 1:
        front(); // 执行一次舵机动作
        actionstate = 0;
        break;
    case 2:
        left(); // 执行一次舵机动作
        actionstate = 0;
        break;
    case 3:
        right(); // 执行一次舵机动作
        actionstate = 0;
        break;
    case 4:
        back(); // 执行一次舵机动作
        actionstate = 0;
        break;
    case 5:
        toplefthand(); // 执行一次舵机动作
        actionstate = 0;
        break;
    case 6:
        toprighthand(); // 执行一次舵机动作
        actionstate = 0;
        break;
   
    case 10:
        dosleep(); // 执行一次舵机动作
        actionstate = 0;
        break;
    case 7:
        lie(); // 执行一次舵机动作
        actionstate = 0;
        break;
    case 8:
        sitdown(); // 执行一次舵机动作
        actionstate = 0;
        break;
    case 9:
        emojiState = random(0, 7); // 执行一次舵机动作
        actionstate = 0;
        break;
    default:
        break;
    }

    switch (emojiState)
    {
    case 0: // 首页
        u8g2.setFont(u8g2_font_ncenB14_tr);
        do
        {

            u8g2.drawXBMP(0, 0, 128, 64, hi);
        } while (u8g2.nextPage());

        break;
    case 1: // 第二页

        u8g2.setFont(u8g2_font_ncenB14_tr);
        do
        {

            u8g2.drawXBMP(0, 0, 128, 64, angry);
        } while (u8g2.nextPage());

        break;
    case 2: // 第三页
        do
        {
            u8g2.setFont(u8g2_font_ncenB14_tr);
            u8g2.drawXBMP(0, 0, 128, 64, error);
        } while (u8g2.nextPage());

        break;
    case 3: // 第四页
        do
        {
            u8g2.setFont(u8g2_font_ncenB14_tr);
            u8g2.drawXBMP(0, 0, 128, 64, dowhat);
        } while (u8g2.nextPage());

        break;
    case 4: // 第四页

        do
        {
            u8g2.setFont(u8g2_font_ncenB14_tr);
            u8g2.drawXBMP(0, 0, 128, 64, love);
        } while (u8g2.nextPage());
        break;
    case 5: // 第四页

        do
        {
            u8g2.setFont(u8g2_font_ncenB14_tr);
            u8g2.drawXBMP(0, 0, 128, 64, sick);
        } while (u8g2.nextPage());
        break;
    case 6: // 第四页
        do
        {
            u8g2.setFont(u8g2_font_ncenB14_tr);
            u8g2.drawXBMP(0, 0, 128, 64, yun);
        } while (u8g2.nextPage());

        break;
    case 7: // 第四页
        if (WiFi.status() != WL_CONNECTED)
        {
            do
            {
                u8g2.setFont(u8g2_font_ncenB08_tr);
                u8g2.drawXBMP(0, 0, 64, 64, wifi);
                u8g2.drawStr(64, 20, "IP:");
                u8g2.drawStr(64, 40, "192.168.4.1");
                u8g2.drawStr(64, 60, "Need NET");
            } while (u8g2.nextPage());
        }
        else
        {
            fetchWeather();
        }
        break;

        break;
    case 8: // 第四页
        if (WiFi.status() != WL_CONNECTED)
        {
            do
            {
                u8g2.setFont(u8g2_font_ncenB08_tr);
                u8g2.drawXBMP(0, 0, 64, 64, wifi);
                u8g2.drawStr(64, 20, "IP:");
                u8g2.drawStr(64, 40, "192.168.4.1");
                u8g2.drawStr(64, 60, "Need NET");
            } while (u8g2.nextPage());
        }
        else
        {
            do
            {
                timeClient.update(); // 更新时间
                u8g2.setFont(u8g2_font_ncenB14_tr);
                timeClient.update();
                u8g2.drawXBMP(0, 0, 64, 64, timeimage);
                // 获取当前时间
                // 显示时间到 OLED
                int currentHour = timeClient.getHours();
                int currentMinute = timeClient.getMinutes();
                String timeToDisplay = String(currentHour) + ":" + String(currentMinute);
                u8g2.drawStr(64, 30, "TIME");
                u8g2.setCursor(64, 50);
                u8g2.print(timeToDisplay);

            } while (u8g2.nextPage());
        }
        break;
    case 9: // 第四页

        do
        {
            u8g2.setFont(u8g2_font_ncenB14_tr);
            u8g2.drawXBMP(0, (64 / 2 - 22 / 2), 128, 22, logo);
        } while (u8g2.nextPage());
        break;
    default:
        // 添加默认 case 来处理其他情况
        break;
    }

    delay(100);
}
