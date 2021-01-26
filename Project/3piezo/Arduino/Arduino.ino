#include <Tone.h>

#define FREQ_DIV 4

Tone tone0;
Tone tone1;
Tone tone2;

const int leds[] = {3, 4, 5};
bool isPlaying[3] = {0};
int notes[3][6] = {
  {NOTE_G3, NOTE_GS3, NOTE_A4, NOTE_AS4, NOTE_B4, NOTE_C4},
  {NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3},
  {NOTE_G2, NOTE_GS2, NOTE_A3, NOTE_AS3, NOTE_B3, NOTE_C3}
};
int frets[3] = {0};
float scale;

void setup() {
  Serial.begin(9600);

  pinMode(leds[2], OUTPUT);
  pinMode(leds[1], OUTPUT);
  pinMode(leds[0], OUTPUT);

  tone0.begin(8);
  tone1.begin(9);
  tone2.begin(10);

}

void loop() {
  if (Serial.available() > 0) {
    char key = Serial.read();
    Serial.println(key);

    switch (key) {
      case 'z':
        frets[2] = 0;
        break;
      case 'x':
        frets[2] = 1;
        break;
      case 'c':
        frets[2] = 2;
        break;
      case 'v':
        frets[2] = 3;
        break;
      case 'b':
        frets[2] = 4;
        break;
      case 'n':
        frets[2] = 5;
        break;
      case 'a':
        frets[1] = 0;
        break;
      case 's':
        frets[1] = 1;
        break;
      case 'd':
        frets[1] = 2;
        break;
      case 'f':
        frets[1] = 3;
        break;
      case 'g':
        frets[1] = 4;
        break;
      case 'h':
        frets[1] = 5;
        break;
      case 'q':
        frets[0] = 0;
        break;
      case 'w':
        frets[0] = 1;
        break;
      case 'e':
        frets[0] = 2;
        break;
      case 'r':
        frets[0] = 3;
        break;
      case 't':
        frets[0] = 4;
        break;
      case 'y':
        frets[0] = 5;
        break;
      
      case 'm':
        if (isPlaying[2]) {
          isPlaying[2] = false;
          digitalWrite(leds[2], LOW);
          tone2.stop();
        } else {
          isPlaying[2] = true;
          digitalWrite(leds[2], HIGH);
        }
        break;
      case 'k':
        if (isPlaying[1]) {
          isPlaying[1] = false;
          digitalWrite(leds[1], LOW);
          tone1.stop();
        } else {
          isPlaying[1] = true;
          digitalWrite(leds[1], HIGH);
        }
        break;
      case 'o':
        if (isPlaying[0]) {
          isPlaying[0] = false;
          digitalWrite(leds[0], LOW);
          tone0.stop();
        } else {
          isPlaying[0] = true;
          digitalWrite(leds[0], HIGH);
        }
        break;
    };

    if (isPlaying[2]) {
      scale = analogRead(A2) / 512.0;
      tone2.play((int) (notes[2][frets[2]] * FREQ_DIV * scale));
    }
    if (isPlaying[1]) {
      scale = analogRead(A1) / 512.0;
      tone1.play((int) (notes[1][frets[1]] * FREQ_DIV * scale));
    }
    if (isPlaying[0]) {
      scale = analogRead(A0) / 512.0;
      tone0.play((int) (notes[0][frets[0]] * FREQ_DIV * scale));
    }
    
  }
}
