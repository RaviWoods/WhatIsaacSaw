#include <Servo.h>

Servo myServo;
byte servoPin = 9;

void setup() {
   myServo.attach(servoPin);
   myServo.writeMicroseconds(1500);
}

void loop() {
  myServo.write(80);
  delay(180);
  myServo.write(100);
  delay(180);
}
