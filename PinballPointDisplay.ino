/*
Made by: Connor Hutcheson 12/11/2022
*/
int DataPin = 2;
int LatchPin = 3;
int ClockPin = 4;

/*
  7 segment display segment layout:
  |-------------|
  |      A      |
  |             |
  |F           B|
  |             |
  |      G      |
  |E           C|
  |             |
  |      D      |
  |           DP|
  |-------------|

*/
//Segments: G,F,A,B,DP,C,D,E
//list of all the numbers
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

long numw = 59209;

void setup() {
  pinMode(LatchPin, OUTPUT);
  pinMode(DataPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  Serial.begin(9600);
  //Serial.println((num%10 - num%1)/1);
  //Serial.println((num%100 - num%10)/10);
  //Serial.println((num%1000 - num%100)/100);
}

void loop() {
  shiftNum(DataPin, ClockPin, LatchPin, numw);
}


void shiftNum(int dpin, int cpin, int lpin, long num) {
  for (long i = 1; num % i != num; i *= 10) {
    delay(250);
    digitalWrite(lpin, LOW);
    shiftOut(dpin, cpin, LSBFIRST, nums[i]);
    digitalWrite(lpin, HIGH);
    Serial.println("Displayed: ");
    Serial.print(nums[i], BIN);
    Serial.println((num % (i * 10) - num % (i)) / i);
  }
}
