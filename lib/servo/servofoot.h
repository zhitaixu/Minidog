#ifndef SERVOFOOT_H
#define SERVOFOOT_H

#include <Servo.h>

extern Servo servo1;
extern Servo servo2;
extern Servo servo3;
extern Servo servo4;

void setupServo(uint8_t engine1, uint8_t engine2, uint8_t engine3, uint8_t engine4);

void front();
void back();
void left();
void right();
void sitdown();
void lie();
void toplefthand();
void toprighthand();
void dosleep();




#endif
