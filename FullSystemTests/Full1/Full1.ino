#include <Servo.h>

// Declare Pin outs
const int drawerPin = 2; 
const int needleUpSwitchPin = 3;
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
const int downTime = 180;
Servo myServo;

enum State {
  justClosed,
  fullyClosed,
  justOpen,
  fullyOpen
};

State systemState = fullyOpen;

void setup() {
  // Serial.begin(9600);
}

void loop() {
  boolean drawerState = digitalRead(drawerPin);
  
  if ((systemState == fullyOpen || systemState == justOpen) && drawerState) {
    delay(100);
    if(digitalRead(drawerPin)) {
      systemState = justClosed;
    } else {
      systemState = fullyOpen;
    }
  } else if ((systemState == fullyOpen || systemState == justOpen) && !drawerState)  {
    systemState = fullyOpen;
  } else if ((systemState == fullyClosed || systemState == fullyOpen) && drawerState) {
    systemState = fullyClosed;
  } else if ((systemState == fullyClosed || systemState == fullyOpen) && drawerState) {
    delay(100);
    if(digitalRead(drawerPin)) {
      systemState = fullyClosed;
    } else {
      systemState = justOpen;
    }
  }
  
  switch (systemState) {
    case fullyOpen:
      break;
    case justOpen:
      moveNeedles("down");
      break;
    case fullyClosed:
      //TODO Add Lights Code
      playTune();
      break;
    case justClosed: 
      moveNeedles("up");
      break;
  }
} 

void moveNeedles(String direction) {
  if(direction == "up") {
    myServo.attach(servoPin);
    while(!digitalRead(needleUpSwitchPin)) {
      myServo.write(upSpeed);  
    };
    myServo.detach();
  } else if (direction == "down") {
    myServo.attach(servoPin);
    myServo.write(downSpeed);
    delay(downTime);
    myServo.detach();
  }
  return;
}

void playTune() {
  int sensorReading = analogRead(pot1Pin);
  
  //Serial.println(sensorReading);
 
  /* map the analog input range (in this case, 0 - 1023 from the potentiometer)
  to the output pitch range (lowFreq to highFreq)
  the change prompted by info on this website: https://www.teachmeaudio.com/mixing/techniques/audio-spectrum
  */
  
  int thisPitch = map(sensorReading, 0, 1023, lowFreq, highFreq);

  tone(speakerPin, thisPitch, 100);
  delay(1); 
  return;
}




