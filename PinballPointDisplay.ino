/*
  This code is very much a BETA version.
  It is NOT complete and will probably need to be
  tweaked a lot to work for you. Some of the bits
  in this code are completely reduandant and were
  just me messing around. Some bits can be
  deleted as you see fit.
*/
int DataPin = 8;
int LatchPin = 9;
int ClockPin = 10;
int NumberOfDisplays = 3;

#define sol1 4
#define sol2 6
#define sol3 13

int debounce = 500; //in milliseconds

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


uint32_t count = 0;

int s1, s2, s3;

bool laststate1, laststate2, laststate3;  // false = low; high = true;


void activateSolenoid(uint8_t triggerPin, uint8_t solenoidPin, bool override) {
  if (override == true) {
    digitalWrite(solenoidPin, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (triggerPin == HIGH) {
    digitalWrite(solenoidPin, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(solenoidPin, LOW);
    digitalWrite(LED_BUILTIN, LOW);
  }
}
void setup() {
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  pinMode(6, OUTPUT);
  pinMode(11, INPUT);
  pinMode(13, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(LatchPin, OUTPUT);
  pinMode(DataPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  Serial.begin(9600);
  shiftNum(0);
  //Serial.println((num%10 - num%1)/1);
  //Serial.println((num%100 - num%10)/10);
  //Serial.println((num%1000 - num%100)/100);
}
int currentTime;
int lastTime;
bool lock = false;
void loop() {
  currentTime = millis();
  s1 = digitalRead(3);
  s2 = digitalRead(5);
  s3 = digitalRead(11);

  activateSolenoid(s1, sol1, false);
  activateSolenoid(s2, sol2, false);
  activateSolenoid(s3, sol3, lock);
  if (s1 == HIGH && s1 != laststate1) {
    count++;
    shiftNum(count);
  }
  if (s2 == HIGH && s2 != laststate2) {
    count++;
    shiftNum(count);
  }
  if (s3 == HIGH && s3 != laststate3 && lock == false) {
    count++;
    shiftNum(count);
    lock = true;
    lastTime = currentTime;
  }
  if(lock){
    if(currentTime - lastTime == debounce){
      lock = false;
    }
  }

  laststate1 = s1;
  laststate2 = s2;
  laststate3 = s3;
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
