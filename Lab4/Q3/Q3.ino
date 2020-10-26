#include <Servo.h>

Servo myservo;  // create servo object to control a servo

String degree;

void setup() {
  Serial.begin(9600);
  myservo.attach(2);  // attaches the servo on pin 9 to the servo object
}

void loop() {

  if (Serial.available() > 0) {
    char digit = Serial.read();
    
    if (digit == 13){
      myservo.write(degree.toInt());
  
      degree = "";
    } else {
      degree += digit;
    }
  }
}
