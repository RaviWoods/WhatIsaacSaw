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


void setup(){
  Serial.begin(9600);
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
} 
  

void updateControl(){
  aSin.setFreq(int(map(mozziAnalogRead(A0),0,1023,0,3000))); // set the frequency
  aSin2.setFreq(int(map(mozziAnalogRead(A1),0,1023,0,3000)));
  aSin3.setFreq(int(map(mozziAnalogRead(A2),0,1023,0,3000)));
  aSin4.setFreq(int(map(mozziAnalogRead(A3),0,1023,0,3000)));
  //Serial.println(mozziAnalogRead(A0)*3);
  //Serial.println(mozziAnalogRead(A1)*3);
  // put changing controls in here
}


int updateAudio(){
  return aSin2.next()+aSin3.next()+aSin4.next(); // return an int signal centred around 0
}


void loop(){
  audioHook(); // required here
}



