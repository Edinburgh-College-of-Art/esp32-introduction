//=============================================================
// File:    ESP32_ExpansionBoard_ServoPot.ino
//
// Author:  J. Hathway 2025
//
// Description:
//     - Use potentiometer to control servo position
//=============================================================

#define SERVO_PIN 12
#define POT_PIN 32

#include <ESP32Servo.h>
Servo servo;

void setup() {
  // Attach pin to servo object
  servo.attach(SERVO_PIN);
}

void loop() {
  // Get potentiometer value
  int potValue = analogRead(POT_PIN);

  // Scale pot value from 0-4095 to 0-180
  int position = map(potValue, 0, 4095, 0, 180);

  // Set servo position
  servo.write(position);
  delay(15);  // short delay to not overload loop
}