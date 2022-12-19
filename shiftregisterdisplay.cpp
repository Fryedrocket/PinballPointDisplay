#include "Arduino.h"

#include "shiftregisterdisplay.h"

shiftregisterdisplay::shiftregisterdisplay(int numberOfDisplays, int DataPin, int ClockPin, int LatchPin) {
  this->numberOfDisplays = numberOfDisplays;
  this->DataPin = DataPin;
  this->ClockPin = ClockPin;
  this->LatchPin = LatchPin;

  pinMode(DataPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  pinMode(LatchPin, OUTPUT);

  Serial.begin(9600);
}

void shiftregisterdisplay::displayNumber(unsigned long displayNumber) {
  //digitalWrite(LatchPin, LOW);
  for (int i = 1; displayNumber % i != displayNumber; i *= 10) {
    digitalWrite(LatchPin, LOW);      
    delay(500);
    shiftOut(DataPin, ClockPin, LSBFIRST, number[(displayNumber % (i * 10) - displayNumber % (i)) / i]);
    Serial.println("Displayed: ");
    Serial.print((displayNumber % (i * 10) - displayNumber % (i)) / i);
    digitalWrite(LatchPin, HIGH);
  }
  //digitalWrite(LatchPin, HIGH);
}

void shiftregisterdisplay::changeSegmentOrder(char segmentOrder[8]) {
  this->segmentOrder[8] = segmentOrder[8];

  for (int i = 0; i < 8; i++) {
    bool running = true;
    for (int j = 0; running == true; j++) {
      if (segment[j] == segmentOrder[i]) {
        //debugging
        Serial.println("Found segment " + String(segment[i]) + " at index: " + String(j));
        segments[i] = B10000000 >> j;
        Serial.println(segments[i], HEX);
        running = false;
      }
    }
  }
  // number zero
  number[0] |= segments[0];  //A
  number[0] |= segments[1];  //B
  number[0] |= segments[2];  //C
  number[0] |= segments[3];  //D
  number[0] |= segments[4];  //E
  // number one
  number[1] |= segments[1];  //B
  number[1] |= segments[2];  //C
  // number two
  number[2] |= segments[0];  //A
  number[2] |= segments[1];  //B
  number[2] |= segments[3];  //D
  number[2] |= segments[4];  //E
  number[2] |= segments[6];  //G
  // number three
  number[3] |= segments[0];  //A
  number[3] |= segments[1];  //B
  number[3] |= segments[2];  //C
  number[3] |= segments[3];  //D
  number[3] |= segments[6];  //G
  // number four
  number[4] |= segments[1];  //B
  number[4] |= segments[2];  //C
  number[4] |= segments[5];  //F
  number[4] |= segments[6];  //G
  // number five
  number[5] |= segments[0];  //A
  number[5] |= segments[2];  //C
  number[5] |= segments[3];  //D
  number[5] |= segments[5];  //F
  number[5] |= segments[6];  //G
  // number six
  number[6] |= segments[2];  //C
  number[6] |= segments[3];  //D
  number[6] |= segments[4];  //E
  number[6] |= segments[5];  //F
  number[6] |= segments[6];  //G
  // number seven
  number[7] |= segments[0];  //A
  number[7] |= segments[1];  //B
  number[7] |= segments[2];  //C
  // number eight
  number[8] |= segments[0];  //A
  number[8] |= segments[1];  //B
  number[8] |= segments[2];  //C
  number[8] |= segments[3];  //D
  number[8] |= segments[4];  //E
  number[8] |= segments[5];  //F
  number[8] |= segments[6];  //G
  // number nine
  number[9] |= segments[0];  //A
  number[9] |= segments[1];  //B
  number[9] |= segments[2];  //C
  number[9] |= segments[3];  //D
  number[9] |= segments[5];  //F
  number[9] |= segments[6];  //G
}