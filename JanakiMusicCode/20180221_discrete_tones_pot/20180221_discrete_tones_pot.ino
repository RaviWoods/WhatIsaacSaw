/*
  Pitch follower

 Plays a pitch that changes based on a changing analog input

 circuit:
 * 8-ohm speaker on digital pin 9
 * photoresistor on analog 0 to 5V
 * 4.7K resistor on analog 0 to ground

 created 21 Jan 2010
 modified 31 May 2012
 by Tom Igoe, with suggestion from Michael Flynn

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Tone2

 */


void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);
}

void loop() {
  // read the sensor:
  int sensorReading = analogRead(A0);
  // float is translating the analog number set to voltage; Why 600.0? Because it sound better than 1023.)
  float voltage = sensorReading * (5.0 / 600);
  // print out the value you read:
  Serial.println(voltage);
  // print the sensor reading so you know its range
 // Serial.println(sensorReading);
  // map the analog input range (in this case, 0 - 5V from the potentiometer)
  // to the output pitch range ("120 - 1500Hz" from orig sketch changed to "60-2000Hz")
  // the change prompted by info on this website: https://www.teachmeaudio.com/mixing/techniques/audio-spectrum
  // change the minimum and maximum input numbers below
  // depending on the range your sensor's giving:
  int thisPitch = map(voltage, 0, 5, 60, 2000);

  // play the pitch:
  tone(9, thisPitch, 100);
  delay(1);        // delay in between reads for stability
}






