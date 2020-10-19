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

String op1, op2;
char _operator;
boolean operator_entered = false;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void loop() {
//  lcd.clear();

  char key = keypad.getKey();
  
  if (key){
    lcd.print(key);

    if (key == 'o')
    {
      op1 = "";
      op2 = "";
      operator_entered = false;
      lcd.clear();
      lcd.setCursor(0, 0);
    }
    else if (key == '=')
    {
      int o1 = op1.toInt();
      int o2 = op2.toInt();
      lcd.setCursor(0, 1);

      switch (_operator)
      {
        case '+':
          lcd.print(o1 + o2);
          break;
        case '-':
          lcd.print(o1 - o2);
          break;
        case '*':
          lcd.print(o1 * o2);
          break;
        case '/':
          lcd.print((float)o1 / o2);
          break;
      }
      
    }
    else if (!operator_entered && (key == '+' || key == '-' || key == '*' || key == '/'))
    {
      _operator = key;
      operator_entered = true;
    }
    else if (! operator_entered)
    {
      op1 += key;
    }
    else
    {
      op2 += key;
    }

    Serial.println("Op1: " + op1);
    Serial.print("Op:  ");
    Serial.println(_operator);
    Serial.println("Op2: " + op2);
  }
  
}
