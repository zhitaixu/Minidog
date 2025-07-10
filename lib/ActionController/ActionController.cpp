
#include "ActionController.h"

ActionController::ActionController(int pin1, int pin2, int pin3, int pin4) {
    setupServo(pin1, pin2, pin3, pin4);
}

void ActionController::begin() {
    // Initialization if needed, setupServo is already called in constructor
}

void ActionController::performAction(int action) {
    switch (action) {
        case 1: front(); break;
        case 2: left(); break;
        case 3: right(); break;
        case 4: back(); break;
        case 5: toplefthand(); break;
        case 6: toprighthand(); break;
        case 7: lie(); break;
        case 8: sitdown(); break;
        case 10: dosleep(); break;
        default: break;
    }
}
