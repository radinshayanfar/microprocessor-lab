// include the library code:
#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'7','8','9', '/'},
  {'4','5','6', '*'},
  {'1','2','3', '-'},
  {'o','0','=', '+'}
};
byte rowPins[ROWS] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {23, 25, 27, 29}; //connect to the column pinouts of the keypad

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte col = 0;
byte row = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  lcd.clear();
  lcd.setCursor(col, row);
  lcd.print("Radin");

  col++;
  if (col == 12)
  {
    col = 0;
    row = 1 - row;
  }

  delay(100);
  
}
