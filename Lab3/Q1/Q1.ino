// include the library code:
#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;

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
