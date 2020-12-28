#include "pitches.h"

#include "jingle_bells.h"
//#include "Ode_to_Joy.h"
//#include "the_imperial_march.h"
//#include "frere_jacques.h"
//#include "ey_iran.h"

#define TEMPO 210
//#define TEMPO 150
//#define TEMPO 150
//#define TEMPO 135
//#define TEMPO 210

const int potPin = A0, buttonPin = 0, soundPin = 8;

bool play = false;
float scale;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  play = 1 - digitalRead(buttonPin);
  
  if (play) {
    for (int note = 0; note < sizeof(melody) / sizeof(int); note++) {
      scale = analogRead(potPin) / 512.0;
      int duration = 2 * 60 * 1000.0 / (TEMPO * noteDurations[note]);
      tone(soundPin, (int) (melody[note] * scale), duration);
      delay( (int) duration );
      if (digitalRead(buttonPin)) {
        break;
      }
    }
  }
}
