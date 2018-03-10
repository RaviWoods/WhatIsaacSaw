#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, PIN, NEO_GRB + NEO_KHZ800); // set up for 6 Neopixels

void setup() {

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  
  rainbow(250); // integer determines the speed
  rainbowCycle(40); // integer determines the speed

}

// rainbow tweaked: showing only the range of colours without red
// this is defined in Wheel2
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
