//=============================================================
// File:    ESP32_ExpansionBoard_ServoSweep.ino
//
// Author:  J. Hathway 2025
//
// Description:
//     - Sweep servo motor from 0-180 degrees and back
//=============================================================

#define SERVO_PIN 12

#include <ESP32Servo.h>
Servo servo;

void setup() {
  // Attach pin to servo object
  servo.attach(SERVO_PIN);
}

void loop() {
  // 0 degrees to 180 degrees
  for (int pos = 0; pos <= 180; pos++) { 
    servo.write(pos); // update servo position
    delay(15);                     
  }

  // 0 degrees to 180 degrees
  for (int pos = 180; pos >= 0; pos--) {
    servo.write(pos);  // update servo position
    delay(15);                       
  }
}