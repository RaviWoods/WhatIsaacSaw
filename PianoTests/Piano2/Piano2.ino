//Polyphonic music using Arduino tone() function
//Including "Super Mario Theme" test music
//
//Code: M. Eric Carr / Paleotechnologist.net
// eric( atsign ) paleotechnologist dot net
//            CC-BY-NC

//Sheet music from http://kafi.website/mario-theme-song-trumpet-sheet-music/


#include "pitches.h"

void qnRest() {delay(280);}
void enRest() {delay(140);}

void setup() {
  
}



void loop() {
  playQnTetrad(analogRead(A0)*2,analogRead(A1)*2,analogRead(A2)*2,analogRead(A3)*2);
  enRest();
  delay(10);  //Seems to fix the unresponsive serial port
}

void playQnTetrad(int noteA, int noteB, int noteC, int noteD) {
  //280ms for a quarter note
  const int NOTEDELAY = 13;  //ms
  const int REPS = 5; //Number of loops for this chord
  int n;
  for (n = 0; n < REPS; n++) {
    tone(8, noteA);
    delay(NOTEDELAY);
    tone(8, noteB);
    delay(NOTEDELAY);
    tone(8, noteC);
    delay(NOTEDELAY);
    tone(8, noteD);
    delay(NOTEDELAY);
  }
  noTone(5);
}//playQnTetrad()
