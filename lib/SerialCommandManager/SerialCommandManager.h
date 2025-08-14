#ifndef SERIALCOMMANDMANAGER_H
#define SERIALCOMMANDMANAGER_H

#include <Arduino.h>

class SerialCommandManager {
public:
    SerialCommandManager();
    void begin(unsigned long baudRate = 9600);
    void update();
    void setActionCallback(void (*callback)(int action));
    
private:
    void (*actionCallback)(int action);
    String commandBuffer;
    bool processCommand(const String& command);
};

#endif // SERIALCOMMANDMANAGER_H 