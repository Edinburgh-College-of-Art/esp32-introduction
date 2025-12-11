//=============================================================
// File:    ESP32_ExpansionBoard_Potentiometer.ino
//
// Author:  J. Hathway 2025
//
// Description:
//     - Read potentiometer and print value to Serial Monitor
//=============================================================

#define POT_PIN 32

void setup() {
  // Start serial communication
  Serial.begin(115200);
}

void loop() {
  int potValue = analogRead(POT_PIN);  // get potentiomer value
  Serial.println(potValue);            // print to Serial Monitor

  delay(15);  // Short delay to not oveload the loop
}