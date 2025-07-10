#include "servofoot.h"
#include <Arduino.h>

// --- Action Sequence Definitions ---

const ActionStep STAND_UP_SEQUENCE[] = {
    {90, 90, 90, 90, 500}
};

const ActionStep FRONT_SEQUENCE[] = {
    {90, 140, 40, 90, 200},
    {40, 140, 40, 140, 200},
    {40, 90, 90, 140, 200},
    {90, 90, 90, 90, 200} // Return to neutral
};

const ActionStep BACK_SEQUENCE[] = {
    {90, 40, 140, 90, 200},
    {140, 40, 140, 40, 200},
    {140, 90, 90, 40, 200},
    {90, 90, 90, 90, 200} // Return to neutral
};

const ActionStep SITDOWN_SEQUENCE[] = {
    {90, 140, 90, 40, 1000},
    {90, 90, 90, 90, 1000} // Stand up slowly
};

const ActionStep LIE_SEQUENCE[] = {
    {180, 0, 0, 180, 1000},
    {90, 90, 90, 90, 1000} // Stand up slowly
};

const ActionStep SLEEP_SEQUENCE[] = {
    {0, 180, 180, 0, 500}
};

const ActionStep LEFT_SEQUENCE[] = {
    {100, 90, 60, 90, 150},
    {140, 90, 40, 90, 150},
    {90, 90, 90, 90, 150},
    {90, 120, 90, 80, 150},
    {90, 140, 90, 90, 150},
    {90, 90, 90, 90, 150}
};

const ActionStep RIGHT_SEQUENCE[] = {
    {80, 90, 120, 90, 150},
    {40, 90, 140, 90, 150},
    {90, 90, 90, 90, 150},
    {90, 60, 90, 100, 150},
    {90, 40, 90, 90, 150},
    {90, 90, 90, 90, 150}
};

const ActionStep TOP_LEFT_HAND_SEQUENCE[] = {
    {90, 90, 0, 90, 200},
    {90, 90, 30, 90, 200},
    {90, 90, 0, 90, 200},
    {90, 90, 30, 90, 200},
    {90, 90, 90, 90, 200}
};

const ActionStep TOP_RIGHT_HAND_SEQUENCE[] = {
    {180, 90, 90, 90, 200},
    {150, 90, 90, 90, 200},
    {180, 90, 90, 90, 200},
    {150, 90, 90, 90, 200},
    {90, 90, 90, 90, 200}
};


// --- Class Implementation ---

ActionSequencer::ActionSequencer(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) {
    _servo1.attach(pin1, 500, 2500);
    _servo2.attach(pin2, 500, 2500);
    _servo3.attach(pin3, 500, 2500);
    _servo4.attach(pin4, 500, 2500);
}

void ActionSequencer::begin() {
    setServoPositions({90, 90, 90, 90, 0}); // Initial position
}

void ActionSequencer::update() {
    if (!isBusy()) {
        return;
    }

    unsigned long current_time = millis();
    if (current_time - _step_start_time >= _current_sequence[_current_step].duration_ms) {
        _current_step++;
        if (_current_step >= _total_steps) {
            // Sequence finished
            _current_sequence = nullptr;
            _current_step = 0;
            _total_steps = 0;
        } else {
            // Start next step
            setServoPositions(_current_sequence[_current_step]);
            _step_start_time = current_time;
        }
    }
}

void ActionSequencer::startAction(ActionType action) {
    if (isBusy()) return; // Don't start a new action if one is running

    switch (action) {
        case ACTION_STAND_UP:
            _current_sequence = STAND_UP_SEQUENCE;
            _total_steps = sizeof(STAND_UP_SEQUENCE) / sizeof(ActionStep);
            break;
        case ACTION_FRONT:
            _current_sequence = FRONT_SEQUENCE;
            _total_steps = sizeof(FRONT_SEQUENCE) / sizeof(ActionStep);
            break;
        case ACTION_BACK:
            _current_sequence = BACK_SEQUENCE;
            _total_steps = sizeof(BACK_SEQUENCE) / sizeof(ActionStep);
            break;
        case ACTION_SITDOWN:
            _current_sequence = SITDOWN_SEQUENCE;
            _total_steps = sizeof(SITDOWN_SEQUENCE) / sizeof(ActionStep);
            break;
        case ACTION_LIE:
            _current_sequence = LIE_SEQUENCE;
            _total_steps = sizeof(LIE_SEQUENCE) / sizeof(ActionStep);
            break;
        case ACTION_SLEEP:
            _current_sequence = SLEEP_SEQUENCE;
            _total_steps = sizeof(SLEEP_SEQUENCE) / sizeof(ActionStep);
            break;
        case ACTION_LEFT:
            _current_sequence = LEFT_SEQUENCE;
            _total_steps = sizeof(LEFT_SEQUENCE) / sizeof(ActionStep);
            break;
        case ACTION_RIGHT:
            _current_sequence = RIGHT_SEQUENCE;
            _total_steps = sizeof(RIGHT_SEQUENCE) / sizeof(ActionStep);
            break;
        case ACTION_TOP_LEFT_HAND:
            _current_sequence = TOP_LEFT_HAND_SEQUENCE;
            _total_steps = sizeof(TOP_LEFT_HAND_SEQUENCE) / sizeof(ActionStep);
            break;
        case ACTION_TOP_RIGHT_HAND:
            _current_sequence = TOP_RIGHT_HAND_SEQUENCE;
            _total_steps = sizeof(TOP_RIGHT_HAND_SEQUENCE) / sizeof(ActionStep);
            break;
        // Add other actions here...
        default:
            return; // Unknown action
    }

    _current_step = 0;
    setServoPositions(_current_sequence[0]);
    _step_start_time = millis();
}

bool ActionSequencer::isBusy() {
    return _current_sequence != nullptr;
}

void ActionSequencer::setServoPositions(const ActionStep& step) {
    _servo1.write(step.servo1_angle);
    _servo2.write(step.servo2_angle);
    _servo3.write(step.servo3_angle);
    _servo4.write(step.servo4_angle);
}