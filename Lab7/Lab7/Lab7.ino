#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Wire.h>

#define DEVICE_ADDRESS 0b1010000
#define SAVE_ADDRESS  50

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'o', '0', '=', '+'}
};
byte rowPins[ROWS] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {23, 25, 27, 29}; //connect to the column pinouts of the keypad

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ledPins[4] = {53, 52, 51, 50};
// =============================================================== //

enum State {idle, changeTime, work, paused, finished} state = idle;
String prompts[] = {"IDLE", "Ch time: ", " working", "Paused", "FINISHED"};
byte chTimeStage = 0;
byte currentStage = 0;
uint8_t totalTimes[4] = {2, 5, 3, 4};
String inputBuffer;
bool timerOn = false;
int timerTime = totalTimes[0];
float diff;
long t0 = millis();
long prevSave = millis();

void eeprom_write(uint16_t memory_address, uint8_t* data, int _size);
void eeprom_read(uint16_t memory_address, uint8_t* data, int _size);
void pPrompt(String prompt = "");
void saveState();
void loadState();
float calc_time();

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);

  for (int i = 0; i < 4; i++)
    pinMode(ledPins[i], OUTPUT);

  loadState();
}

void loop() {
  float timer = calc_time();
  lcd.setCursor(0, 1);
  lcd.print("Timer: " + String(timer) + "  ");

  char key = keypad.getKey();
  if (key) {
    //    Serial.println(state);

    if (state == idle && (key >= '1' && key <= '4')) {
      state = changeTime;
      chTimeStage = key - '0' - 1;
      pPrompt();
    } else if (state == changeTime && key == '=') {
      state = idle;
      totalTimes[chTimeStage] = inputBuffer.toInt();
      pPrompt();
    } else if (state == work && key == '*') {
      state = paused;
      timerOn = false;
      timerTime = diff;
      pPrompt();
    } else if (state == idle && key == '*') {
      state = work;
      timerTime = totalTimes[0];
      currentStage = 0;
      t0 = millis();
      timerOn = true;
      digitalWrite(ledPins[0], HIGH);
      pPrompt(String(currentStage + 1));
    } else if (state == paused && key == '*') {
      state = work;
      t0 = millis();
      timerOn = true;
      timerTime = diff;
      pPrompt(String(currentStage + 1));
    } else if (state == finished && key == '*') {
      state = idle;
      for (int i = 0; i < 4; i++)
        digitalWrite(ledPins[i], LOW);
      pPrompt();
    } else if (state == changeTime) {
      lcd.setCursor(prompts[state].length() + inputBuffer.length(), 0);
      lcd.print(key);
      inputBuffer += key;
    }

  }

  if ((millis() - prevSave) > 2000) {
    saveState();
    prevSave = millis();
  }
  delay(100);

}

void loadState() {
  uint8_t read_data[10] = {0};
  eeprom_read(SAVE_ADDRESS, read_data, 10);
  if (read_data[0] == 255)
    return;

  state = read_data[0];
  currentStage = read_data[1];
  for (int i = 0; i < 4; i++)
    totalTimes[i] = read_data[2 + i];
  diff = timerTime = *(float*)(read_data + 6);

  if (state == work) {
    timerOn = true;
    digitalWrite(ledPins[currentStage], HIGH);
    pPrompt(String(currentStage + 1));
  } else {
    if (state == finished) {
      for (int i = 0; i < 4; i++)
        digitalWrite(ledPins[i], HIGH);
    } else if (currentStage == paused) {
      digitalWrite(ledPins[currentStage], HIGH);
    }

    pPrompt();
  }
}

void saveState() {
  uint8_t write_data[10] = {0};
  write_data[0] = (uint8_t) state;
  write_data[1] = (uint8_t) currentStage;
  for (int i = 0; i < 4; i++)
    write_data[2 + i] = totalTimes[i];
  *(float*)(write_data + 6) = diff;

  eeprom_write(SAVE_ADDRESS, write_data, 10);
}

void pPrompt(String prompt = "") {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(prompt + prompts[state]);
  inputBuffer = "";
}

void eeprom_write(uint16_t memory_address, uint8_t* data, int _size) {
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write((uint8_t)((memory_address & 0xFF00) >> 8));
  Wire.write((uint8_t)((memory_address & 0x00FF) >> 0));
  for (int i = 0; i < _size; i++) {
    Wire.write(data[i]);
    Serial.print("Writing: ");
    Serial.println(data[i]);
    delay(50);
  }
  Wire.endTransmission();
  delay(50);
}

void eeprom_read(uint16_t memory_address, uint8_t* data, int _size) {
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write((uint8_t)((memory_address & 0xFF00) >> 8));
  Wire.write((uint8_t)((memory_address & 0x00FF) >> 0));
  Wire.endTransmission();

  Wire.requestFrom(DEVICE_ADDRESS, _size);
  for (int i = 0; i < _size; i++) {
    data[i] = Wire.read();
  }
}

void nextStage() {
  currentStage = (currentStage + 1) % 4;
  if (currentStage == 0) {
    timerOn = false;
    state = finished;
    for (int i = 0; i < 4; i++)
      digitalWrite(ledPins[i], HIGH);
    pPrompt();
    return;
  }
  t0 = millis();
  timerTime = totalTimes[currentStage];
  digitalWrite(ledPins[currentStage - 1], LOW);
  digitalWrite(ledPins[currentStage], HIGH);
  pPrompt(String(currentStage + 1));
}

float calc_time() {
  if (!timerOn) {
    return diff;
  }
  long nowT = millis();
  diff = (float) timerTime - ((nowT - t0) / 1000.0);
  if (diff <= 0) {
    nextStage();
    diff = 0;
  }
  return diff;
}
