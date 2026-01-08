//=============================================================
// File:    WiFi_Connect.ino
//
// Author:  J. Hathway 2025
//
// Description:
//     - This sketch will connect the ESP32 board to a 
//       specified Wi-Fi network.
//     - You will need to replace the ssid and password
//       variables with your own Wi-Fi network name and
//       password.
//     - This sketch will ONLY confirm whether or not the ESP32
//       has been able to connect to the specified network.
//=============================================================

#include <WiFi.h>
  
//=============================================================
// **REPLACE THESE VARIABLES WITH YOUR DETAILS**
#define WIFI_NAME "WiFiNetworkName"
#define WIFI_PASSWORD "WiFiNetworkPassword"
//=============================================================
  
void setup() {
  // Start serial communication
  Serial.begin(115200);
  Serial.println("ESP32 Connect to Wi-Fi Example");
  delay(1000);
  
  // Initialise in Station Mode
  WiFi.mode(WIFI_STA);
  
  // Start connecting
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  Serial.println("Connecting to" + String(WIFI_NAME) + "...");
  
  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) { delay(400); }
  
  Serial.print("Connected!");
}
  
void loop() {}