#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, PIN, NEO_GRB + NEO_KHZ800); // Setup for 6 Neopixels

// Declare Pin outs
const int drawerPin = 2;
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
int rainbowNumber = 0;
static unsigned long last_interrupt_time = 0;
String needleMove = "none";

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(drawerPin, INPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  Serial.begin(9600);
  systemState = LOW;
  myServo.attach(servoPin);
  digitalWrite(8,LOW);
  moveNeedles("down");
}

void loop() {
  
  if (systemState == HIGH) {
    rainbowCycleUpdate();
    rainbowCycleUpdate();
    rainbowCycleUpdate();
    rainbowCycleUpdate();
    playQnTetrad(analogRead(A0)*2,analogRead(A1)*2,analogRead(A2)*2,analogRead(A3)*2);
  }
  
  int drawerState = digitalRead(drawerPin);
  if((systemState == HIGH && !drawerState) || (systemState == LOW && drawerState) ) {
    if (millis() - last_interrupt_time > switchDebounceTime) {
      Serial.println("motor");
      if (systemState == HIGH && !drawerState) {
        systemState = LOW;
        ledOff();
        rainbowNumber = 0;
        moveNeedles("down");
      } else if (systemState == LOW && drawerState) {
        systemState = HIGH;
        moveNeedles("up");  
      }
    }
    last_interrupt_time = millis();    
  }
  
  //Serial.println(digitalRead(drawerPin));
  //Serial.println(systemState);
  //Serial.println("--");
}


void moveNeedles(String direction) {
  //Serial.println("moveNeedles");
  delay(1);
  if (direction == "up") {
    int upStart = millis();
    //Serial.println("upM");
    for (pos = pos; pos >= 0; pos -= 1) { 
      // in steps of 1 degree
      myServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(servoWaitTime);                       // waits 15ms for the servo to reach the position
    }
    int upEnd = millis();
    //Serial.println("up2");
    //Serial.println(upEnd - upStart);
  } else if (direction == "down") {
    myServo.write(downSpeed);
    int downStart = millis();
    //Serial.println("downM");
    for (pos = 0; pos <= maxAngle; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(servoWaitTime);                       // waits 15ms for the servo to reach the position
    }
    int downEnd = millis();
    //Serial.println("down2");
    //Serial.println(downEnd - downStart);
  }
  delay(1);
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

void qnRest() {noTone(8); delay(280);}
void enRest() {noTone(8); delay(140);}

void playQnTetrad(int noteA, int noteB, int noteC, int noteD) {
  const int NOTEDELAY = 13;  //ms
  const int REPS = 5; //Number of loops for this chord
  int n;
  for (n = 0; n < REPS; n++) {
    tone(8, noteA);
    delay(NOTEDELAY);
    tone(8, noteB);
    delay(NOTEDELAY);
  }
  for (n = 0; n < REPS; n++) {
    tone(8, noteC);
    delay(NOTEDELAY);
    tone(8, noteD);
    delay(NOTEDELAY);
  }
  noTone(NOTEDELAY);
}


void ledOff() {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

void rainbowUpdate() {
  uint16_t i, j;
  if(rainbowNumber > 255) {
    rainbowNumber = 0;
  }
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel2((i+rainbowNumber) & 255));
  }
  strip.show();
  rainbowNumber++;
}

void rainbowCycleUpdate() {
  
  uint16_t i, j;

  for(i=0; i< strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + rainbowNumber) & 255));
  }
  strip.show();
  rainbowNumber++;
}

void rainbow(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel2((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// NOTE: transistion between rainbow and rainbowCycle needs to be improved 

// This makes the rainbow equally distributed throughout
// This one uses the standard Wheel
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
} 

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel2(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(0, 255 - WheelPos * 3, WheelPos * 3);//255 - WheelPos * 3,0, WheelPos * 3
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3); //0, WheelPos * 3, 255 - WheelPos * 3
  }
  WheelPos -= 170;
  return strip.Color(0, 255 - WheelPos * 3, WheelPos * 3);//WheelPos * 3, 255 - WheelPos * 3, 0
}



