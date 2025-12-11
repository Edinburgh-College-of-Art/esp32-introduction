//=============================================================
// File:    USBSerial_Send.ino
//
// Author:  J. Hathway 2025
//
// Description:
//     - Send some simple messages via USB Serial
//     - Upload this sketch and open Serial Monitor to see 
//       outgoing messages.
//=============================================================

void setup() {
  // Start serial communication
  Serial.begin(115200);
}

void loop() {
  // String data
  Serial.print("Hello");
  Serial.println(" World");

  // Integer values
  Serial.println(12345);
  Serial.println(67890);

  // Float values
  Serial.println(3.14159);

  // Formatting
  Serial.print("\t"); // Tab
  Serial.print("\n"); // New line

  // Short delay so it doesn't print too quickly to read
  delay(1000);
}