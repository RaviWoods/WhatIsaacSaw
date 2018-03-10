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

bool flip = HIGH;

int systemState;

void setup() {
  Serial.begin(9600);
  moveNeedles("up");
  //attachInterrupt(digitalPinToInterrupt(drawerPin), drawerMove, CHANGE);
  systemState = 0;
}

void loop() {
  if(systemState == 1) {
    playTune();
  }
  if(digitalRead(drawerPin) && !systemState) {
    Serial.println("close");
    systemState = 1;
    moveNeedles("down");
    delay(50);
  } else if (!digitalRead(drawerPin) && systemState) {
    Serial.println("open");
    systemState = 0;
    moveNeedles("up");
    delay(50);
  }
  Serial.println(digitalRead(drawerPin));
  Serial.println(systemState);
  Serial.println("--");
  digitalWrite(LED_BUILTIN, flip);
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
  // read the sensor:
  int sensorReading = analogRead(A0);
  //float voltage = sensorReading * (5.0 / 950.0);
  // print out the value you read:
  // print the sensor reading so you know its range
 // Serial.println(sensorReading);
  // map the analog input range (in this case, 0 - 5 from the potentiometer)
  // to the output pitch range ("120 - 1500Hz" from orig sketch changed to "60-2000Hz")
  // the change prompted by info on this website: https://www.teachmeaudio.com/mixing/techniques/audio-spectrum
  // change the minimum and maximum input numbers below
  // depending on the range your sensor's giving:
  int thisPitch = map(sensorReading, 0, 1023, 60, 2000);
  Serial.println(thisPitch);
  // play the pitch:
  tone(9, thisPitch, 100);
  delay(1);        // delay in between reads for stability§
}






