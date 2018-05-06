// Globals
const int dataPin1 = 11; // BLUE WIRE TENS 
const int dataPin2 = 8; // BLUE WIRE UNITS 
const int latchPin1 = 12; // GREEN WIRE TENS
const int latchPin2 = 9; // GREEN WIRE UNITS
const int clockPin = 10; // yellow to 74HC595 pin 11
// uncomment one of the following lines that describes your display
// and comment out the line that does not describe your display
//const char common = 'a'; // common anode
const char common = 'c'; // common cathode
const int rollover = 10;
int units = 0;
int tens = 0;

byte symbol, symbols[] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  };

void setup() {
  // initialize I/O pins
  pinMode(dataPin1, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  pinMode(latchPin1, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin, OUTPUT);
  // cathode stuff for seven seg
  if( common == 'a' )
  for(int i=0; i<sizeof(symbols); i++)
  symbols[i] ^= B11111111;

  // making sure tens stays off while units hasn't reached 9
  digitalWrite(latchPin1, LOW); // prepare shift register for data
  shiftOut(dataPin1, clockPin, LSBFIRST, B00000000);
  digitalWrite(latchPin1, HIGH);
}


// checks if units and tens are both at 9 (meaning it must reset)
void loop() {
  if(tens == 9 && units == 9){
      units = 0;
      tens = 0;
  }else {
      incrementUnits();
      delay(500);
  }
}


// increments the units seg and if on rollover, increments the tens
void incrementUnits()
{
      if (units == 10){
      units =0;
      incrementTens();
      }
      digitalWrite(latchPin2, LOW); // prepare shift register for data
      shiftOut(dataPin2, clockPin, LSBFIRST, symbols[units]);
      digitalWrite(latchPin2, HIGH);
      units++ %rollover;
}

// increments the tens
void incrementTens()
{
      tens = tens +1;
      digitalWrite(latchPin1, LOW); // prepare shift register for data
      shiftOut(dataPin1, clockPin, LSBFIRST, symbols[tens]);
      digitalWrite(latchPin1, HIGH);
}
