/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
//#include <Keypad.h>
//
//const byte ROWS = 4; //four rows
//const byte COLS = 4; //three columns
//char keys[ROWS][COLS] = {
//  {'7','8','9', '/'},
//  {'4','5','6', '*'},
//  {'1','2','3', '-'},
//  {'o','0','=', '+'}
//};
//byte rowPins[ROWS] = {22, 23, 24, 25}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {26, 27, 28, 29}; //connect to the column pinouts of the keypad

const byte ledPins[9] = {A0, A1, A2, A3, A4, A5, A6, A7, A8};

//Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

byte incomingByte = 0; // for incoming serial data

void setup(){
  Serial.begin(9600);

  for (byte i = 0; i < 9; i++)
    pinMode(ledPins[i], OUTPUT);
}
  
void loop(){
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // turn on corresponding led
    digitalWrite(ledPins[incomingByte - '0' - 1], HIGH);
  }
};
