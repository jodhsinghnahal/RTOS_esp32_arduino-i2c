#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
}

void loop() {
  static bool buttonState5 = false;
  static bool buttonState6 = false;
  static bool buttonState7 = false;
  static bool buttonState8 = false;
  static bool buttonState9 = false;

  if (!digitalRead(5)) {
    buttonState5 = !buttonState5;
  }
  if (!digitalRead(6)) {
    buttonState6 = !buttonState6;
  }
  if (!digitalRead(7)) {
    buttonState7 = !buttonState7;
  }
  if (!digitalRead(8)) {
    buttonState8 = !buttonState8;
  }
  if (!digitalRead(9)) {
    buttonState9 = !buttonState9;
  }

  String buttons = String(buttonState5) + String(buttonState6) + String(buttonState7) + String(buttonState8) + String(buttonState9);

  Wire.beginTransmission(9);
  Wire.write(buttons.c_str());
  Wire.endTransmission();

  delay(200);
}
