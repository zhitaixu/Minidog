#ifndef ACTIONSEQUENCER_H
#define ACTIONSEQUENCER_H

#include <Servo.h>

// Defines a single step in a sequence
struct ActionStep {
    int servo1_angle;
    int servo2_angle;
    int servo3_angle;
    int servo4_angle;
    int duration_ms;
};

// Enum for all possible actions
enum ActionType {
    ACTION_NONE,
    ACTION_FRONT,
    ACTION_BACK,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_SITDOWN,
    ACTION_LIE,
    ACTION_TOP_LEFT_HAND,
    ACTION_TOP_RIGHT_HAND,
    ACTION_SLEEP,
    ACTION_STAND_UP
};

class ActionSequencer {
public:
    ActionSequencer(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
    void begin();
    void update();
    void startAction(ActionType action);
    bool isBusy();

private:
    Servo _servo1, _servo2, _servo3, _servo4;
    const ActionStep* _current_sequence = nullptr;
    int _current_step = 0;
    int _total_steps = 0;
    unsigned long _step_start_time = 0;

    void setServoPositions(const ActionStep& step);
};

#endif // ACTIONSEQUENCER_H