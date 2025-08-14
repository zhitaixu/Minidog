#include "SerialCommandManager.h"

SerialCommandManager::SerialCommandManager() : actionCallback(nullptr), commandBuffer("") {
}

void SerialCommandManager::begin(unsigned long baudRate) {
    Serial.begin(baudRate);
    Serial.println("串口命令管理器已启动");
    Serial.println("可用命令:");
    Serial.println("1 - 前进");
    Serial.println("2 - 左转");
    Serial.println("3 - 右转");
    Serial.println("4 - 后退");
    Serial.println("5 - 左上举手");
    Serial.println("6 - 右上举手");
    Serial.println("7 - 躺下");
    Serial.println("8 - 坐下");
    Serial.println("10 - 睡觉");
    Serial.println("s - 状态查询");
    Serial.println("h - 帮助信息");
}

void SerialCommandManager::update() {
    while (Serial.available()) {
        char c = Serial.read();
        
        if (c == '\n' || c == '\r') {
            if (commandBuffer.length() > 0) {
                processCommand(commandBuffer);
                commandBuffer = "";
            }
        } else {
            commandBuffer += c;
        }
    }
}

void SerialCommandManager::setActionCallback(void (*callback)(int action)) {
    actionCallback = callback;
}

bool SerialCommandManager::processCommand(const String& command) {
    String cmd = command;
    cmd.trim();
    cmd.toLowerCase();
    
    Serial.print("收到命令: ");
    Serial.println(cmd);
    
    if (cmd == "1") {
        Serial.println("执行: 前进");
        if (actionCallback) actionCallback(1);
        return true;
    }
    else if (cmd == "2") {
        Serial.println("执行: 左转");
        if (actionCallback) actionCallback(2);
        return true;
    }
    else if (cmd == "3") {
        Serial.println("执行: 右转");
        if (actionCallback) actionCallback(3);
        return true;
    }
    else if (cmd == "4") {
        Serial.println("执行: 后退");
        if (actionCallback) actionCallback(4);
        return true;
    }
    else if (cmd == "5") {
        Serial.println("执行: 左上举手");
        if (actionCallback) actionCallback(5);
        return true;
    }
    else if (cmd == "6") {
        Serial.println("执行: 右上举手");
        if (actionCallback) actionCallback(6);
        return true;
    }
    else if (cmd == "7") {
        Serial.println("执行: 躺下");
        if (actionCallback) actionCallback(7);
        return true;
    }
    else if (cmd == "8") {
        Serial.println("执行: 坐下");
        if (actionCallback) actionCallback(8);
        return true;
    }
    else if (cmd == "10") {
        Serial.println("执行: 睡觉");
        if (actionCallback) actionCallback(10);
        return true;
    }
    else if (cmd == "s" || cmd == "status") {
        Serial.println("=== 机器人状态 ===");
        Serial.println("串口通信: 正常");
        Serial.println("系统运行: 正常");
        Serial.println("可用动作: 前进、左转、右转、后退、举手、躺下、坐下、睡觉");
        return true;
    }
    else if (cmd == "h" || cmd == "help") {
        Serial.println("=== 帮助信息 ===");
        Serial.println("数字命令:");
        Serial.println("  1 - 前进");
        Serial.println("  2 - 左转");
        Serial.println("  3 - 右转");
        Serial.println("  4 - 后退");
        Serial.println("  5 - 左上举手");
        Serial.println("  6 - 右上举手");
        Serial.println("  7 - 躺下");
        Serial.println("  8 - 坐下");
        Serial.println("  10 - 睡觉");
        Serial.println("其他命令:");
        Serial.println("  s/status - 状态查询");
        Serial.println("  h/help - 帮助信息");
        return true;
    }
    else {
        Serial.print("未知命令: ");
        Serial.println(cmd);
        Serial.println("输入 'h' 或 'help' 查看帮助");
        return false;
    }
} 