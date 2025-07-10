
#include "adc.h"

// Note: Global variables batteryVoltage and batteryPercentage are now defined in main.cpp

// 采样器内部变量
static long totalAdcValue = 0;
static int sampleCount = 0;
static unsigned long lastSampleTime = 0;
static float lastAverageVoltage = 0;
static bool samplingDone = false;

void initAdcSampler() {
    totalAdcValue = 0;
    sampleCount = 0;
    lastSampleTime = 0;
    lastAverageVoltage = 0;
    samplingDone = false;
}

void updateAdcSampler() {
    unsigned long now = millis();
    
    if (sampleCount < numSamples) {
        if (now - lastSampleTime >= 10) { // 每10ms采一次
            lastSampleTime = now;

            int adc = analogRead(A0);
            totalAdcValue += adc;
            sampleCount++;
        }
    } else {
        if (!samplingDone) {
            // 采满numSamples后，计算平均
            float averageAdcValue = totalAdcValue / (float)numSamples;
            lastAverageVoltage = (averageAdcValue / 1023.0) * 1.0; // 1.0V参考电压
            samplingDone = true;
        }
    }
}

bool isAdcSamplingDone() {
    return samplingDone;
}

float getLastAverageVoltage() {
    samplingDone = false; // 读一次后，准备重新采样
    totalAdcValue = 0;
    sampleCount = 0;
    return lastAverageVoltage;
}

int mapBatteryPercentage(float voltage) {
    if (voltage <= minVoltage) return 0;
    if (voltage >= maxVoltage) return 100;
    return (int)((voltage - minVoltage) / (maxVoltage - minVoltage) * 100);
}
