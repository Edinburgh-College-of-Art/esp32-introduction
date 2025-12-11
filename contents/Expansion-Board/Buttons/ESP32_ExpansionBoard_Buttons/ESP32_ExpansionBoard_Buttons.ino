//=============================================================
// File:    ESP32_ExapansionBoard_Buttons.ino
//
// Author:  J. Hathway 2025
//
// Description:
//     - Print the button values from the ESP32 Expansion board
//       to the Serial Monitor.
//=============================================================

// Pin definitions
#define BUTTON_0 14
#define BUTTON_1 27
#define BUTTON_2 26
#define BUTTON_3 25

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Initialise pullup pins
  pinMode(BUTTON_0, INPUT_PULLUP);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
}

void loop() {
  Serial.print("b0=");
  Serial.print(digitalRead(BUTTON_0));

  Serial.print(", b1=");
  Serial.print(digitalRead(BUTTON_1));

  Serial.print(", b2=");
  Serial.print(digitalRead(BUTTON_2));

  Serial.print(", b3=");
  Serial.print(digitalRead(BUTTON_3));
  Serial.println();

  // Short delay to not overload the loop
  delay(10);
}