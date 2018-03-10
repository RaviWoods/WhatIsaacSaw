#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, PIN, NEO_GRB + NEO_KHZ800); // Setup for 6 Neopixels

Servo myServo;

// Declare Pin outs
const int drawerPin = 2;
const int speakerPin = 8;
const int servoPin = 12;
const int ledPin =  13;
const int pot1Pin =  A0;
const int pot2Pin =  A1;
const int pot3Pin =  A2;
const int pot4Pin =  A3;

/* State of System
LOW is when Drawer is Open, Needles are up and Music is stopped
HIGH is when Drawer is Closed, Needles are down, Music is playing, and Lights are on
*/
bool systemState = LOW;

const int NOTEDELAY = 13; //Length of each note
const int servoWaitTime = 7; // Time Servo Waits on each turn
const int maxAngle = 100; //Angle of Servo when Needles are Down
const int switchDebounceTime = 50; //Wait time for debounce of limit switch

int numPixelUpdates = 4;
int servoPos = 0;
int rainbowNumber = 0;
static unsigned long last_interrupt_time = 0;

void setup() {
  // Initialize all pixels to 'off'
  strip.begin();
  strip.show(); 

  // Initialise Pin Outs
  pinMode(drawerPin, INPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  
  //Serial.begin(9600);

  //Move Needles up initially
  myServo.attach(servoPin);
  moveNeedles("up");
}

void loop() {

  // When system is on, the NeoPixel updates, and a chord is played
  if (systemState == HIGH) {

    for (int i = 0; i <= numPixelUpdates; i++) {
       rainbowCycleUpdate();
    }
   
    playTetrad(analogRead(pot1Pin)*2,analogRead(pot2Pin)*2,analogRead(pot3Pin)*2,analogRead(pot4Pin)*2); // Notes of the Chord are based on 4 potentiometer inputs
  }
  
  int drawerState = digitalRead(drawerPin);

  // If the state of the system and the drawer are different, and the switch isn't bouncing, update the system state
  if((systemState == HIGH && !drawerState) || (systemState == LOW && drawerState) ) {
    if (millis() - last_interrupt_time > switchDebounceTime) {
      //Serial.println("motor");
      if (systemState == HIGH && !drawerState) {
        // Drawer is now open, so LED should be switched off, and needles should be moved up
        systemState = LOW;
        ledOff();
        rainbowNumber = 0;
        moveNeedles("up");
      } else if (systemState == LOW && drawerState) {
        // Drawer is now closed, so needles should be moved down
        systemState = HIGH;
        moveNeedles("down");  
      }
    }
    last_interrupt_time = millis(); //  Update Time since last update, to stop debounce
  }
  
  //Serial.println(digitalRead(drawerPin));
  //Serial.println(systemState);
  //Serial.println("--");
}


void moveNeedles(String direction) {
  //Serial.println("moveNeedles");
  delay(1);

  
  if (direction == "up") {
    // If direction is up, move servo to position 0
    for (servoPos = servoPos; servoPos >= 0; servoPos -= 1) { 
      myServo.write(servoPos);
      delay(servoWaitTime);
    }
  } else if (direction == "down") {
    // If direction is down, move servo to the maxAngle
    for (servoPos = 0; servoPos <= maxAngle; servoPos += 1) {
      myServo.write(servoPos); 
      delay(servoWaitTime);
    }
  }
  delay(1);
  return;
}

void qnRest() {noTone(8); delay(280);}
void enRest() {noTone(8); delay(140);}

void playTetrad(int noteA, int noteB, int noteC, int noteD) {
  /* Music plays as two chords, of two notes each
   * A chord is heard by switching between the two notes very quickly, which we percieve as a chord
   */
  const int REPS = 5; //Number of loops for this chord
  int n;
  for (n = 0; n < REPS; n++) {
    tone(speakerPin, noteA);
    delay(NOTEDELAY);
    tone(speakerPin, noteB);
    delay(NOTEDELAY);
  }
  for (n = 0; n < REPS; n++) {
    tone(speakerPin, noteC);
    delay(NOTEDELAY);
    tone(speakerPin, noteD);
    delay(NOTEDELAY);
  }
  noTone(NOTEDELAY);
}

// Function to turn of NeoPixel
void ledOff() {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}


// Update Function to slowly fade NeoPixel from blue, to green, and back to blue
void blueGreenUpdate() {
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

// Update Function to slowly fade NeoPixel through the rainbow
void rainbowCycleUpdate() {
  
  uint16_t i, j;

  for(i=0; i< strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + rainbowNumber) & 255));
  }
  strip.show();
  rainbowNumber++;
}


// Two wheel functions, which turn a number into a position on a colour wheel

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



