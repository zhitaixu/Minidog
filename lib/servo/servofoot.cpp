#include "servofoot.h"

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;


void setupServo(uint8_t engine1, uint8_t engine2, uint8_t engine3, uint8_t engine4)
{
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
