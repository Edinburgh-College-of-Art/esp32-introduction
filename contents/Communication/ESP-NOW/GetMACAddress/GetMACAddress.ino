//==============================================================
// File:    GetMACAddress.ino
//
// Author:  J. Hathway 2026
//
// Description:
//     - This sketch will print the device MAC address to the
//       serial monitor every 2 seconds.
//==============================================================

#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
}

void loop() {
  Serial.println("MAC Address:");
  Serial.println(WiFi.macAddress());
  delay(2000);
}