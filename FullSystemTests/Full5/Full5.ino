#include <Servo.h>
/*  Example playing a sinewave at a set frequency,
    using Mozzi sonification library.
  
    Demonstrates the use of Oscil to play a wavetable.
  
    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or 
    check the README or http://sensorium.github.com/Mozzi/
  
    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users
  
    Tim Barrass 2012, CC by-nc-sa.
*/

#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin2(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin3(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin4(SIN2048_DATA);

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 256 // powers of 2 please
  


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
  startMozzi(CONTROL_RATE);
  systemState = LOW;
  myServo.attach(servoPin);
  myServo.write(0);
}

void updateControl(){
  aSin.setFreq(int(map(mozziAnalogRead(A0),0,1023,0,3000))); // set the frequency
  aSin2.setFreq(int(map(mozziAnalogRead(A1),0,1023,0,3000)));
  aSin3.setFreq(int(map(mozziAnalogRead(A2),0,1023,0,3000)));
  aSin4.setFreq(int(map(mozziAnalogRead(A3),0,1023,0,3000)));
}

int updateAudio(){
  return aSin.next();
}

void loop() {

  /*
  if((systemState == HIGH && !digitalRead(drawerPin)) || (systemState == LOW && digitalRead(drawerPin)) ) {
    if (millis() - last_interrupt_time > switchDebounceTime) {
      Serial.println("motor");
      if (systemState == HIGH && !digitalRead(drawerPin)) {
        systemState = LOW;
        
        moveNeedles("up");
        pauseMozzi();
      } else if (systemState == LOW && digitalRead(drawerPin)) {
        systemState = HIGH;
        
        moveNeedles("down");  
        unPauseMozzi();
      }
    }
    last_interrupt_time = millis();    
  }
  */
  audioHook();  
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


void drawerMove() {
  Serial.println("drawerMove");
  int rising = digitalRead("drawerPin");
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 500) {
    Serial.println("interrupt2");
    if (rising == HIGH) {
      Serial.println("down");
      systemState = HIGH;
      needleMove = "down";
    } else {
      Serial.println("up");
      systemState = LOW;
      needleMove = "up";
    }
  }
  last_interrupt_time = interrupt_time;
  return;
}


void playTune() {
  int sensorReading = analogRead(pot1Pin);
  int thisPitch = map(sensorReading, lowPot, highPot, lowFreq, highFreq);
  //Serial.println(thisPitch);
  tone(speakerPin, thisPitch, 10);
  delay(1);
  return;
}







