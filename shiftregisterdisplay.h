#ifndef shiftregisterdisplay_h
#define shiftregisterdisplay_h

#include <Arduino.h>

class shiftregisterdisplay {
private:
  int numberOfDisplays;
  // default segment order
  char segmentOrder[8] = { 'G', 'F', 'A', 'B', 'DP', 'C', 'D', 'E' };
  //segments on the display
  char segment[8] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'DP' };
  // byte storing the position of each segemnt on the shift register
  byte segments[8] = { B00100000, B00010000, B00000100, B00000010, B00000001, B01000000, B10000000, B00001000 };
  // byte storing each segment that needs to be lit up for each number
  byte number[10] = { B01110111,
                      B00010100,
                      B10110011,
                      B10110110,
                      B11010100,
                      B11100110,
                      B11100111,
                      B00110100,
                      B11110111,
                      B11110110 };
  //pins for the shift register connection
  int DataPin;
  int ClockPin;
  int LatchPin;
public:
  shiftregisterdisplay(int numberOfDisplays, char segmentOrder[8], int DataPin, int ClockPin, int LatchPin);

  void displayNumber(unsigned long displayNumber);

  void changeSegmentOrder(char segmentOrder[8]);
};

#endif