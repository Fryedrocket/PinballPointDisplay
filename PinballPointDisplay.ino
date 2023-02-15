int DataPin = 8;
int LatchPin = 9;
int ClockPin = 10;
int NumberOfDisplays = 3;

#include "Edgedetection.h"


byte nums[] = { B01110111,
                B00010100,
                B10110011,
                B10110110,
                B11010100,
                B11100110,
                B11100111,
                B00110100,
                B11110111,
                B11110110 };

//each number individually
byte _0 = B01110111;
byte _1 = B00010100;
byte _2 = B10110011;
byte _3 = B10110110;
byte _4 = B11010100;
byte _5 = B11100110;
byte _6 = B11100111;
byte _7 = B00110100;
byte _8 = B11110111;
byte _9 = B11110110;


int count = 0;

bool laststate1 = false;  // false = low; high = true;
bool laststate2 = false;  // false = low; high = true;

void setup() {
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  pinMode(6, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(LatchPin, OUTPUT);
  pinMode(DataPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  Serial.begin(9600);
  //Serial.println((num%10 - num%1)/1);
  //Serial.println((num%100 - num%10)/10);
  //Serial.println((num%1000 - num%100)/100);
}

void loop() {
  // int pinstate1 = digitalRead(3);
  // if (pinstate1 == HIGH) {
  //   digitalWrite(4, HIGH);
  //   digitalWrite(LED_BUILTIN, HIGH);
  //   if (laststate1 == false) {
  //     count++;
  //     shiftNum(count);
  //     laststate1 = true;
  //   }
  // } else {
  //   digitalWrite(4, LOW);
  //   digitalWrite(LED_BUILTIN, LOW);
  //   laststate1 = false;
  // }
  // int pinstate2 = digitalRead(5);
  // if (pinstate2 == HIGH) {
  //   digitalWrite(6, HIGH);
  //   digitalWrite(LED_BUILTIN, HIGH);
  //   if (laststate2 == false) {
  //     count++;
  //     shiftNum(count);
  //     laststate2 = true;
  //   }
  // } else {
  //   digitalWrite(6, LOW);
  //   digitalWrite(LED_BUILTIN, LOW);
  //   laststate2 = false;
  // }

  //pinDetection(3, RISING_EDGE);
}


void shiftNum(uint32_t num) {
  digitalWrite(LatchPin, LOW);
  int d = 0;
  for (long i = 1; num % i != num; i *= 10) {
    d++;
    shiftOut(DataPin, ClockPin, LSBFIRST, nums[(num % (i * 10) - num % (i)) / i]);
    Serial.print("Displayed: ");
    Serial.print(nums[i], BIN);
    Serial.println("");
    Serial.println((num % (i * 10) - num % (i)) / i);
  }
  if (d < NumberOfDisplays) {
    for (int i = NumberOfDisplays - d; i > 0; i--) {
      shiftOut(DataPin, ClockPin, LSBFIRST, nums[0]);
    }
  }
  digitalWrite(LatchPin, HIGH);
}