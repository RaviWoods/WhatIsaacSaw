//Polyphonic music using Arduino tone() function
//Including "Super Mario Theme" test music
//
//Code: M. Eric Carr / Paleotechnologist.net
// eric( atsign ) paleotechnologist dot net
//            CC-BY-NC

//Sheet music from http://kafi.website/mario-theme-song-trumpet-sheet-music/


#include "pitches.h"

void playEnTriad(int noteA, int noteB, int noteC);
void playEnDuad(int noteA, int noteB);
void playQnDuad(int noteA, int noteB);
void playQnTriad(int noteA, int noteB, int noteC);
void playQnTetrad(int noteA, int noteB, int noteC, int noteD);
void playDQnTriad(int noteA, int noteB, int noteC);
void playTripletTriad(int noteA, int noteB, int noteC);
void qnRest() {delay(280);}
void enRest() {delay(140);}

void setup() {
  //Measure 1
  playEnTriad(NOTE_D3, NOTE_FS4, NOTE_E5);
  playEnTriad(NOTE_D3, NOTE_FS4, NOTE_E5);
  enRest();
  playEnTriad(NOTE_D3, NOTE_FS4, NOTE_E5);
  enRest();
  playEnTriad(NOTE_D3, NOTE_FS4, NOTE_C5);
  playQnTriad(NOTE_D3, NOTE_FS4, NOTE_E5);

  //Measure 2
  playQnTetrad(NOTE_G3, NOTE_G4, NOTE_B4, NOTE_G5);
  qnRest();
  playQnDuad(NOTE_G3, NOTE_G4);
  qnRest();

  //Measure 3
  playDQnTriad(NOTE_G3, NOTE_E4, NOTE_C5);
  playEnTriad(NOTE_E3, NOTE_E4, NOTE_G4);
  qnRest();

  //3-4 tie
  playDQnTriad(NOTE_C3, NOTE_C4, NOTE_E4);

  //Measure 4 after the tie
  playQnTriad(NOTE_F3, NOTE_C4, NOTE_A4);
  playQnTriad(NOTE_G3, NOTE_D4, NOTE_B4);
  playEnTriad(NOTE_FS3, NOTE_CS4, NOTE_AS4);
  playQnTriad(NOTE_F3, NOTE_C4, NOTE_A4);

  //Measure 5
  playTripletTriad(NOTE_E3, NOTE_C4, NOTE_G4);
  playTripletTriad(NOTE_C4, NOTE_G4, NOTE_E5);
  playTripletTriad(NOTE_E4, NOTE_B4, NOTE_G5);
  playQnTriad(NOTE_F4, NOTE_C5, NOTE_A5);
  playEnTriad(NOTE_D4, NOTE_A4, NOTE_F5);
  playEnTriad(NOTE_E4, NOTE_B4, NOTE_G5);

  //Measure 6
  enRest();
  playQnTriad(NOTE_C4, NOTE_A4, NOTE_E5);
  playEnTriad(NOTE_A3, NOTE_E4, NOTE_C5);
  playDQnTriad(NOTE_G3, NOTE_D4, NOTE_B4);

  //Measure 7
  playDQnTriad(NOTE_G3, NOTE_E4, NOTE_C5);
  playEnTriad(NOTE_E3, NOTE_E4, NOTE_G4);
  qnRest();

  //7-8 tie
  playDQnTriad(NOTE_C3, NOTE_C4, NOTE_E4);

  //Measure 8 after the tie
  playQnTriad(NOTE_F3, NOTE_C4, NOTE_A4);
  playQnTriad(NOTE_G3, NOTE_D4, NOTE_B4);
  playEnTriad(NOTE_FS3, NOTE_CS4, NOTE_AS4);
  playQnTriad(NOTE_F3, NOTE_C4, NOTE_A4);

  //Measure 9 (same as Measure 5)
  playTripletTriad(NOTE_E3, NOTE_C4, NOTE_G4);
  playTripletTriad(NOTE_C4, NOTE_G4, NOTE_E5);
  playTripletTriad(NOTE_E4, NOTE_B4, NOTE_G5);
  playQnTriad(NOTE_F4, NOTE_C5, NOTE_A5);
  playEnTriad(NOTE_D4, NOTE_A4, NOTE_F5);
  playEnTriad(NOTE_E4, NOTE_B4, NOTE_G5);

  //Measure 10 (same as Measure 6)
  enRest();
  playQnTriad(NOTE_C4, NOTE_A4, NOTE_E5);
  playEnTriad(NOTE_A3, NOTE_E4, NOTE_C5);
  playDQnTriad(NOTE_G3, NOTE_D4, NOTE_B4);

  //Measure 11
  tone(8, NOTE_C3);
  delay(280); //Single quarter note
              //(Pick up the dotted part with the treble;
              // there should be little or no tone gap
              // doing it this way.)
  //noTone(8);              
  playEnTriad(NOTE_C3,NOTE_E5,NOTE_G5); //C3 is from the DQN
  playEnTriad(NOTE_G3,NOTE_DS5,NOTE_FS5);
  playEnDuad(NOTE_D5,NOTE_F5);
  playEnDuad(NOTE_B4,NOTE_DS5);          //Just the high two first
  playEnTriad(NOTE_C4,NOTE_B4,NOTE_DS5); //Start the C4 here
  playEnTriad(NOTE_C4,NOTE_C5,NOTE_E5);  //C4 continues with new top

  //Measure 12
  tone(8,NOTE_F3);
  delay(280); //Quarter part of the DQN
  playEnTriad(NOTE_F3,NOTE_E4,NOTE_GS4);
  playEnDuad(NOTE_F4,NOTE_A4);
  playEnTriad(NOTE_C4,NOTE_A4,NOTE_C5);
  tone(8,NOTE_C4);
  delay(140);//Half of the eighth
  playEnDuad(NOTE_C4,NOTE_A4);
  //Have to split the low QN here
  playEnTriad(NOTE_F3,NOTE_E4,NOTE_C5);
  playEnTriad(NOTE_F3,NOTE_F4,NOTE_D5);

  //Measure 13
  tone(8,NOTE_C3); //Qn part of low DQN
  playEnTriad(NOTE_C3,NOTE_E5,NOTE_G5);
  playEnTriad(NOTE_E3,NOTE_DS5,NOTE_FS5);
  playEnDuad(NOTE_D5,NOTE_F5);
  playEnDuad(NOTE_B4,NOTE_DS5); //Have to split it
  playEnTriad(NOTE_G3,NOTE_B4,NOTE_DS5);
  playEnTriad(NOTE_C4,NOTE_C5,NOTE_E5);
  
  //Measure 14
  enRest();
  playQnTriad(NOTE_F5,NOTE_G5,NOTE_C6);
  playEnTriad(NOTE_F5,NOTE_G5,NOTE_C6);
    
  //Measure 15 (same as 11)
  tone(8, NOTE_C3);
  delay(280); //Single quarter note
              //(Pick up the dotted part with the treble;
              // there should be little or no tone gap
              // doing it this way.)
  //noTone(8);              
  playEnTriad(NOTE_C3,NOTE_E5,NOTE_G5); //C3 is from the DQN
  playEnTriad(NOTE_G3,NOTE_DS5,NOTE_FS5);
  playEnDuad(NOTE_D5,NOTE_F5);
  playEnDuad(NOTE_B4,NOTE_DS5);          //Just the high two first
  playEnTriad(NOTE_C4,NOTE_B4,NOTE_DS5); //Start the C4 here
  playEnTriad(NOTE_C4,NOTE_C5,NOTE_E5);  //C4 continues with new top

  //Measure 16
  tone(8,NOTE_F3);
  delay(140);     //Dotted part of DQN
  playEnTriad(NOTE_F3,NOTE_E4,NOTE_GS4);
  playEnTriad(NOTE_F3,NOTE_F4,NOTE_A4);
  playEnTriad(NOTE_C3,NOTE_A4,NOTE_C5);
  tone(8,NOTE_C4);
  delay(140);
  playEnDuad(NOTE_C4,NOTE_A4);
  playEnTriad(NOTE_F3,NOTE_E4,NOTE_C5);
  playEnTriad(NOTE_F3,NOTE_E4,NOTE_D5);

  //Measure 17
  tone(8,NOTE_C3);
  delay(280);
  playQnTriad(NOTE_GS3,NOTE_GS4,NOTE_DS5);
  enRest();
  playDQnTriad(NOTE_AS3,NOTE_F4,NOTE_D5);

  //Measure 18
  playDQnTriad(NOTE_C4,NOTE_E4,NOTE_C5);
  playEnTriad(NOTE_G3,NOTE_E4,NOTE_C5);  
  tone(8,NOTE_G3);
  delay(280);
  tone(8,NOTE_C3);
  delay(280);

  //Measure 19 (same as 11 and 15)
    tone(8, NOTE_C3);
  delay(280); //Single quarter note
              //(Pick up the dotted part with the treble;
              // there should be little or no tone gap
              // doing it this way.)
  //noTone(8);              
  playEnTriad(NOTE_C3,NOTE_E5,NOTE_G5); //C3 is from the DQN
  playEnTriad(NOTE_G3,NOTE_DS5,NOTE_FS5);
  playEnDuad(NOTE_D5,NOTE_F5);
  playEnDuad(NOTE_B4,NOTE_DS5);          //Just the high two first
  playEnTriad(NOTE_C4,NOTE_B4,NOTE_DS5); //Start the C4 here
  playEnTriad(NOTE_C4,NOTE_C5,NOTE_E5);  //C4 continues with new top



  //Measure 20 (same as 16)
  tone(8,NOTE_F3);
  delay(140);     //Dotted part of DQN
  playEnTriad(NOTE_F3,NOTE_E4,NOTE_GS4);
  playEnTriad(NOTE_F3,NOTE_F4,NOTE_A4);
  playEnTriad(NOTE_C3,NOTE_A4,NOTE_C5);
  tone(8,NOTE_C4);
  delay(140);
  playEnDuad(NOTE_C4,NOTE_A4);
  playEnTriad(NOTE_F3,NOTE_E4,NOTE_C5);
  playEnTriad(NOTE_F3,NOTE_E4,NOTE_D5);



  //Measure 21 (11, 15, 19)
  tone(8, NOTE_C3);
  delay(280); //Single quarter note
              //(Pick up the dotted part with the treble;
              // there should be little or no tone gap
              // doing it this way.)
  //noTone(8);              
  playEnTriad(NOTE_C3,NOTE_E5,NOTE_G5); //C3 is from the DQN
  playEnTriad(NOTE_G3,NOTE_DS5,NOTE_FS5);
  playEnDuad(NOTE_D5,NOTE_F5);
  playEnDuad(NOTE_B4,NOTE_DS5);          //Just the high two first
  playEnTriad(NOTE_C4,NOTE_B4,NOTE_DS5); //Start the C4 here
  playEnTriad(NOTE_C4,NOTE_C5,NOTE_E5);  //C4 continues with new top

  //Measure 22 and on are 14-18 all over again

  //Measure 22 (14)
  enRest();
  playQnTriad(NOTE_F5,NOTE_G5,NOTE_C6);
  playEnTriad(NOTE_F5,NOTE_G5,NOTE_C6);
    
  //Measure 23 (same as 11,15)
  tone(8, NOTE_C3);
  delay(280); //Single quarter note
              //(Pick up the dotted part with the treble;
              // there should be little or no tone gap
              // doing it this way.)
  //noTone(8);              
  playEnTriad(NOTE_C3,NOTE_E5,NOTE_G5); //C3 is from the DQN
  playEnTriad(NOTE_G3,NOTE_DS5,NOTE_FS5);
  playEnDuad(NOTE_D5,NOTE_F5);
  playEnDuad(NOTE_B4,NOTE_DS5);          //Just the high two first
  playEnTriad(NOTE_C4,NOTE_B4,NOTE_DS5); //Start the C4 here
  playEnTriad(NOTE_C4,NOTE_C5,NOTE_E5);  //C4 continues with new top

  //Measure 24 (16)
  tone(8,NOTE_F3);
  delay(140);     //Dotted part of DQN
  playEnTriad(NOTE_F3,NOTE_E4,NOTE_GS4);
  playEnTriad(NOTE_F3,NOTE_F4,NOTE_A4);
  playEnTriad(NOTE_C3,NOTE_A4,NOTE_C5);
  tone(8,NOTE_C4);
  delay(140);
  playEnDuad(NOTE_C4,NOTE_A4);
  playEnTriad(NOTE_F3,NOTE_E4,NOTE_C5);
  playEnTriad(NOTE_F3,NOTE_E4,NOTE_D5);

  //Measure 25 (17)
  tone(8,NOTE_C3);
  delay(280);
  playQnTriad(NOTE_GS3,NOTE_GS4,NOTE_DS5);
  enRest();
  playDQnTriad(NOTE_AS3,NOTE_F4,NOTE_D5);

  //Measure 26 (18)
  playDQnTriad(NOTE_C4,NOTE_E4,NOTE_C5);
  playEnTriad(NOTE_G3,NOTE_E4,NOTE_C5);  
  tone(8,NOTE_G3);
  delay(280);
  tone(8,NOTE_C3);
  delay(280);

  noTone(8);  //MAKE IT STOP! :)

  
  }//setup()



void loop() {
  delay(10);  //Seems to fix the unresponsive serial port
}


void playQnDuad(int noteA, int noteB) {
  //280ms for a quarter note
  const int NOTEDELAY = 19;  //ms
  const int REPS = 7; //Number of loops for this chord
  int n;
  for (n = 0; n < REPS; n++) {
    tone(8, noteA);
    delay(NOTEDELAY);
    tone(8, noteB);
    delay(NOTEDELAY);
  }
  noTone(8);
  delay(14); //280ms total
}//playQnDuad()

void playEnDuad(int noteA, int noteB) {
  //140ms for an eighth note
  const int NOTEDELAY = 15;  //ms
  const int REPS = 4; //Number of loops for this chord
  int n;
  for (n = 0; n < REPS; n++) {
    tone(8, noteA);
    delay(NOTEDELAY);
    tone(8, noteB);
    delay(NOTEDELAY);
  }
  noTone(8);
  delay(20); //140ms total
}//playEnDuad()

void playQnTriad(int noteA, int noteB, int noteC) {
  //280ms for a quarter note
  const int NOTEDELAY = 15;  //ms
  const int REPS = 6; //Number of loops for this chord
  int n;
  for (n = 0; n < REPS; n++) {
    tone(8, noteA);
    delay(NOTEDELAY);
    tone(8, noteB);
    delay(NOTEDELAY);
    tone(8, noteC);
    delay(NOTEDELAY);
  }
  noTone(8);
  delay(10); //280ms total
}//playQnTriad()

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
  noTone(8);
  delay(20); //280ms total
}//playQnTetrad()

void playDQnTriad(int noteA, int noteB, int noteC) {
  //420ms for a dotted quarter note
  const int NOTEDELAY = 15;  //ms
  const int REPS = 9; //Number of loops for this chord
  int n;
  for (n = 0; n < REPS; n++) {
    tone(8, noteA);
    delay(NOTEDELAY);
    tone(8, noteB);
    delay(NOTEDELAY);
    tone(8, noteC);
    delay(NOTEDELAY);
  }
  noTone(8);
  delay(15); //420ms total
}//playDQnTriad()

void playEnTriad(int noteA, int noteB, int noteC) {
  //140ms for an eighth note
  const int NOTEDELAY = 10;  //ms
  const int REPS = 4; //Number of loops for this chord
  int n;
  for (n = 0; n < REPS; n++) {
    tone(8, noteA);
    delay(NOTEDELAY);
    tone(8, noteB);
    delay(NOTEDELAY);
    tone(8, noteC);
    delay(NOTEDELAY);
  }
  noTone(8);
  delay(20); //140ms total for the note
}//playEnTriad()

void playTripletTriad(int noteA, int noteB, int noteC) {
  //186.67ms for a triplet (three QNs fit in two)
  const int NOTEDELAY = 15;  //ms
  const int REPS = 4; //Number of loops for this chord
  int n;
  for (n = 0; n < REPS; n++) {
    tone(8, noteA);
    delay(NOTEDELAY);
    tone(8, noteB);
    delay(NOTEDELAY);
    tone(8, noteC);
    delay(NOTEDELAY);
  }
  noTone(8);
  delay(7); //187ms total
}//playTripletTriad()
