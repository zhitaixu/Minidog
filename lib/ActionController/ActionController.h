
#ifndef ACTIONCONTROLLER_H
#define ACTIONCONTROLLER_H

#include "servofoot.h"

class ActionController {
public:
    ActionController(int pin1, int pin2, int pin3, int pin4);
    void begin();
    void performAction(int action);

private:
    // No private members needed for this simple version
};

#endif // ACTIONCONTROLLER_H
