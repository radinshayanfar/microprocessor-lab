#include <Keypad.h>
#include <Servo.h>

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

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Servo myservo;  // create servo object to control a servo

String degree;

void setup() {
  Serial.begin(9600);
  myservo.attach(2);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  char key = keypad.getKey();
  
  if (key){
    if (key == '*')
    {
      myservo.write(degree.toInt());
      degree = "";
    }
    else if (key >= '0' && key <= '9')
    {
      degree += key;
    }

    Serial.println(degree);
  }
}
