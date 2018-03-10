#include <Servo.h>

// Declare Pin outs
const int drawerPin = 5; 
const int needleUpSwitchPin = 6;
const int speakerPin = 9;
const int servoPin = 10;
const int ledPin =  13;
const int pot1Pin =  A0;
const int pot2Pin =  A1;
const int pot3Pin =  A2;
const int pot4Pin =  A3;

//Low and High frequencies mapped to by the potentiometer
const int lowFreq = 60;
const int highFreq = 2000;

//Speeds of the Servo for moving the needles
const int downSpeed = 80;
const int upSpeed = 100;

// Number of Milliseconds for moving the needles down
const int downTime = 500;
Servo myServo;

enum State {
  justClosed,
  fullyClosed,
  justOpen,
  fullyOpen
};

State systemState = fullyOpen;

void setup() {
  Serial.begin(9600);
  moveNeedles("up");
}

void loop() {
  moveNeedles("down");
  delay(2000);
  moveNeedles("up");
  delay(2000);
  //Serial.println(digitalRead(needleUpSwitchPin));
  //delay(10);
} 

void moveNeedles(String direction) {
  if(direction == "up") {
    Serial.println("up");
    myServo.attach(servoPin);
    while(!digitalRead(needleUpSwitchPin)) {
      myServo.write(upSpeed);  
    };
    myServo.detach();
  } else if (direction == "down") {
    Serial.println("down");
    myServo.attach(servoPin);
    myServo.write(downSpeed);
    delay(downTime);
    myServo.detach();
  }
  return;
}


