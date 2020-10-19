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
String password;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
//  lcd.clear();
  lcd.setCursor(col, 0);

  char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
    lcd.print(key);
    
    if (key == '*')
    {
      lcd.setCursor(0, 1);
      if (password == "1234") {
        lcd.print("Correct password");
      } else {
        lcd.print("Wrong password");
      }
    }

    password += key;
    col++;
  }
  
}
