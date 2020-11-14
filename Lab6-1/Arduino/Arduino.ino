#include <Servo.h>

Servo myservo;  // create servo object to control a servo

const byte lightsLedPin = 22, brakeLightPin = 28, buzzPin = 31, gasPin = 25, servoPin = 8 ;

String inputBuffer;
bool lightsOn = false;
bool gasOn = false;
bool steerMode = false;

void setup() {
  Serial.begin(9600);
  
  myservo.attach(servoPin);
  
  pinMode(lightsLedPin, OUTPUT);
  pinMode(brakeLightPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(gasPin, OUTPUT);

  Serial.println("Actions:\r\n1)Gas pedal\r\n2)Brake pedal\r\n3)Rotate steering wheel\r\n4)Toggle lights\r\n5)Buzz\r\n-----------");
  digitalWrite(brakeLightPin, HIGH);
}

void doAction(int command) {
  if (steerMode) {
    myservo.write(command);
    steerMode = false;
    return;
  }
  
  switch (command) {
    case 1:
      gasOn = true;
      digitalWrite(gasPin, gasOn);
      digitalWrite(brakeLightPin, !gasOn);
      break;
    case 2:
      gasOn = false;
      digitalWrite(gasPin, gasOn);
      digitalWrite(brakeLightPin, !gasOn);
      break;
    case 3:
      steerMode = true;
      Serial.print("Enter degree: ");
      break;
    case 4:
      lightsOn = !lightsOn;
      digitalWrite(lightsLedPin, lightsOn);
      break;
    case 5:
      digitalWrite(buzzPin, HIGH);
      delay(1000);
      digitalWrite(buzzPin, LOW);
      break;
  };
}

void loop() {
  if (Serial.available() > 0) {
    char digit = Serial.read();
    
    if (digit == 13){
      doAction(inputBuffer.toInt());
  
      inputBuffer = "";
    } else {
      inputBuffer += digit;
    }
  }
}
