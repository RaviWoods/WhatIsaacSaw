// pianoChorde 1.0 by C.Forman

// fundamental things
const int numNotes = 4;

// Hardware info
int tonePins[numNotes] = {2,3,4,5};
int speakerPin = 12;
uint8_t outBit;
uint8_t oldSREG;
volatile uint8_t* out;
uint8_t inBits[numNotes];
volatile uint8_t* in[numNotes];

// musical info
float baseFreq = 220.0;
float tones[numNotes];
int period[numNotes];
int dutyCycle[numNotes];
int scale[numNotes]={0,2,4,5};

// playback info
float TimePerSample = 36.0e-6; //microseconds (approx measurement)
int curPhase[numNotes];
float StandardDutyCycle = 0.1;
int i=0;

void setup() {
  Serial.begin(9600);
  // Set up waveform parameters.

  
  // initialise play back arrays and set up hardware
  for (i = 0; i < numNotes; i++) {
     curPhase[i] = 0;
     pinMode (tonePins[i], INPUT);
     inBits[i] = digitalPinToBitMask(tonePins[i]);
     in[i] = portInputRegister(digitalPinToPort(tonePins[i]));
  }
  pinMode(speakerPin, OUTPUT);
  outBit = digitalPinToBitMask(speakerPin);
  out = portOutputRegister(digitalPinToPort(speakerPin));  
  digitalWrite(speakerPin,LOW); // turns off PWM to the output pin (hopefully stays that way).
}

void calculateFreqs(){
  Serial.print("Freqs: ");
  for (i = 0; i < numNotes ; i++) {
      tones[i] = map(analogRead(i),0,1023,200, 500) * pow(2.0,float(scale[i])/12.0);
      Serial.print(tones[i]);
      Serial.print(" ");
  }
  Serial.println(" ");
}

void calculatePeriods(){
  Serial.print("Periods: ");
  for (i = 0; i < numNotes ; i++) {
      period[i] = (int)((1.0/tones[i])/TimePerSample);
      dutyCycle[i] = (int)((float)period[i] * StandardDutyCycle);
      Serial.print(period[i]);
      Serial.print("(");      
      Serial.print(dutyCycle[i]);
      Serial.print(") ");
  }
  Serial.println(" ");  
}

void loop() {
   boolean val=LOW;
   boolean dummy = LOW;
   for (i=0;i<numNotes;i++) {
     if ((curPhase[i] < dutyCycle[i]) && (*(in[i]) & inBits[i])) {
         val = HIGH;
     }
     else {
         dummy = HIGH;
     }
     curPhase[i]++;
     if (curPhase[i]>=period[i]) curPhase[i]=0;
   }

   oldSREG = SREG;
   cli();
   if (val == LOW) {
        *out &= ~outBit;
   } else {
        *out |= outBit;
   }
   SREG = oldSREG;
   calculateFreqs();
   calculatePeriods();
}

