//=============================================================
// File:    ESP32_WiFi_AccessPoint.ino
//
// Author:  J. Hathway 2025
//
// Description:
//     - This sketch will create a Wi-Fi access point on the
//       ESP32.
//     - This allows other devices to connect to this access
//       point in order to communicate with each other.
//     - This does NOT provide a connection to the internet.
//=============================================================

#include <WiFi.h>

//=============================================================
// **REPLACE THESE VARIABLES WITH YOUR DETAILS**
#define WIFI_NAME "WiFiNetworkName"          // You can choose what your access point is called
#define WIFI_PASSWORD "WiFiNetworkPassword"  // You can also set a password for your access point
//=============================================================

void setup() {
  // Start serial communication
  Serial.begin(115200);
  Serial.println("ESP32 Start Access Point Example");
  delay(1000);

  // Initialise Wi-Fi in Access Point Mode
  WiFi.mode(WIFI_AP);

  // Start access point
  while (!WiFi.softAP(WIFI_NAME, WIFI_PASSWORD)) {
    Serial.println("Error: Access Point Failed");
    delay(2000);
  }

  // Print network details to Serial Monitor
  Serial.print("Access Point Created: ");
  Serial.println(WIFI_NAME);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {}