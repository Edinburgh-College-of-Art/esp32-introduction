//=============================================================
// File:    ESP32_ESPNOW_Receive.ino
//
// Author:  J. Hathway 2025
//
// Description:
//     - This sketch will receive any incoming ESP-NOW messages
//       and print them to the Serial Monitor.
//=============================================================

#include <WiFi.h>
#include <esp_now.h>

// Variable to store received messages
String incomingMsg;

//=============================================================
// CALLBACK FUNCTION

// This function is executed when message is received
void callbackFunction(const uint8_t *address, const uint8_t *incomingData, int length) {
  // Clear string variable
  incomingMsg = "";

  // Copy incoming data to message variable
  for (int i = 0; i < length; i++) {
    // If end of strink, break loop
    if ((char)incomingData[i] == '\0') break;
    
    incomingMsg += (char)incomingData[i];
  }

  // Print message to Serial Monitor
  Serial.println("Received: " + incomingMsg);
}

//==============================================================
// SETUP

void setup() {
  // Start serial communication
  Serial.begin(115200);
  Serial.println("ESP-NOW Receive Example");
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  //==============================================================
  // Initialise ESP-NOW

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initialise ESPNOW
  // Do not continue if not initialised
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    while (true) {}
  }

  // Pin callback function
  esp_now_register_recv_cb(callbackFunction);
}

//==============================================================
// LOOP

void loop() {}
