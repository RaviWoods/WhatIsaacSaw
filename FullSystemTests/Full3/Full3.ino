#include <Servo.h>

// Declare Pin outs
const int drawerPin = 2;
const int needleUpSwitchPin = 3;
const int speakerPin = 9;
const int servoPin = 12;
const int ledPin =  13;
const int pot1Pin =  A0;
const int pot2Pin =  A1;
const int pot3Pin =  A2;
const int pot4Pin =  A3;

//Low and High values mapped from the potentiometer
const int lowPot = 0;
const int highPot = 1023;

//Low and High frequencies mapped to by the potentiometer
const int lowFreq = 60;
const int highFreq = 2000;

//Speeds of the Servo for moving the needles
const int downSpeed = 80;
const int upSpeed = 100;

// Number of Milliseconds for moving the needles down
const int downTime = 200;

const int servoWaitTime = 7;
const int maxAngle = 100;
const int switchDebounceTime = 50;
Servo myServo;
bool systemState;
int pos = 0;
static unsigned long last_interrupt_time = 0;
String needleMove = "none";

void setup() {
  pinMode(drawerPin, INPUT);
  pinMode(needleUpSwitchPin, INPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  Serial.begin(9600);
  moveNeedles("up");
  
  systemState = LOW;
  myServo.attach(servoPin);
  myServo.write(0);
}

void loop() {
  if (systemState == HIGH) {
    playTune();
  }
  int drawerState = !digitalRead(drawerPin);
  if((systemState == HIGH && !drawerState) || (systemState == LOW && drawerState) ) {
    if (millis() - last_interrupt_time > switchDebounceTime) {
      Serial.println("motor");
      if (systemState == HIGH && !drawerState) {
        systemState = LOW;
        moveNeedles("up");
      } else if (systemState == LOW && drawerState) {
        systemState = HIGH;
        moveNeedles("down");  
      }
    }
    last_interrupt_time = millis();    
  }
  Serial.println(digitalRead(drawerPin));
  Serial.println(systemState);
  Serial.println("--");
  
}


void moveNeedles(String direction) {
  Serial.println("moveNeedles");
  delay(1);
  if (direction == "up") {
    int upStart = millis();
    Serial.println("upM");
    for (pos = pos; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(servoWaitTime);                       // waits 15ms for the servo to reach the position
    }
    int upEnd = millis();
    Serial.println("up2");
    Serial.println(upEnd - upStart);
  } else if (direction == "down") {
    myServo.write(downSpeed);
    int downStart = millis();
    Serial.println("downM");
    for (pos = 0; pos <= maxAngle; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(servoWaitTime);                       // waits 15ms for the servo to reach the position
    }
    int downEnd = millis();
    Serial.println("down2");
    Serial.println(downEnd - downStart);
  }
  Serial.println("--");
  delay(1);
  Serial.println("stopNeedles");
  return;
}

/* 
void drawerMove() {
  Serial.println("drawerMove");
  int rising = digitalRead("drawerPin");
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 500) {
    Serial.println("interrupt2");
    if (rising == HIGH) {
      Serial.println("down");
      systemState = LOW;
      needleMove = "down";
    } else {
      Serial.println("up");
      systemState = HIGH;
      needleMove = "up";
    }
  }
  last_interrupt_time = interrupt_time;
  return;
}
*/

void playTune() {
  int sensorReading = analogRead(pot1Pin);
  int thisPitch = map(sensorReading, lowPot, highPot, lowFreq, highFreq);
  //Serial.println(thisPitch);
  tone(speakerPin, thisPitch, 10);
  delay(1);
  return;
}







