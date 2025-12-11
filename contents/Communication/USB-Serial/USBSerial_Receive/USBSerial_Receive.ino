//=============================================================
// File:    USBSerial_Receive.ino
//
// Author:  J. Hathway 2025
//
// Description:
//     - Read and parse incoming USB Serial messages.
//     - Upload this sketch and open Serial Monitor to send
//       messages to ESP32.
//=============================================================

void setup() {
  // Start serial communication
  Serial.begin(115200);
}

void loop() {
  // Check for new serial messages
  if (Serial.available()) {
    // Parse message as String
    String incomingMessage = Serial.readStringUntil('\n');

    // Echo message back to Serial Monitor
    Serial.println("Message Received: " + incomingMessage);
  }
}