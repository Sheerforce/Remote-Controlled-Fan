#include <Servo.h>

#define SERVO_DATA_PIN 2

Servo fanservo;

void setup(){
    fanservo.attach(SERVO_DATA_PIN)
    fanservo.write(90);
}

void loop(){
    Serial.println("Callibration finished!")
}
