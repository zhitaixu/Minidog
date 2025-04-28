#ifndef ADC_H
#define ADC_H

#include <Arduino.h>

const float voltageDividerRatio = 8.4;
const float minVoltage = 7.0;
const float maxVoltage = 8.4;
const int numSamples = 10;

extern float batteryVoltage;
extern int batteryPercentage;

// 初始化ADC采样器
void initAdcSampler();
// 非阻塞地更新ADC采样
void updateAdcSampler();
// 是否完成了一轮采样
bool isAdcSamplingDone();
// 获取最后一次平均电压
float getLastAverageVoltage();
// 计算电池电量百分比
int mapBatteryPercentage(float voltage);

#endif
