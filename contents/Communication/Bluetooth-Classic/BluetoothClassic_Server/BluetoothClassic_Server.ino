//=============================================================
// File:    BluetoothClassic_Server.ino
//
// Author:  J. Hathway 2025
//
// Description:
//     - This sketch will initialise the ESP32 as a Bluetooth
//       server.
//     - Once connected to the client device, it will send and
//       receive messages over Bluetooth Serial.
//     - Use Serial Monitor to send messages to paired device.
//=============================================================

#include "BluetoothSerial.h"

BluetoothSerial bluetooth;

#define DEVICE_NAME "ESP32_SERVER"  // this device
#define CLIENT_NAME "ESP32_Client"  // device to connect to

//=============================================================
// SETUP

void setup() {
  // Start serial communication
  Serial.begin(115200);  // for debugging
  Serial.println();

  // Start Bluetooth Serial
  // "true" argument sets this device to be server device
  bluetooth.begin(DEVICE_NAME, true);

  // Connect to client device
  bool connected = false;
  while (!connected) {
    Serial.println("Connecting to " + String(CLIENT_NAME) + "...");
    connected = bluetooth.connect(CLIENT_NAME);  // connect to client
    delay(5000);                                 // time to connect
  }

  Serial.println("Connected.");
}

//=============================================================
// LOOP

void loop() {
  //=========================================================
  // CHECK CONNECTION

  if (!bluetooth.connected()) {

    Serial.println("Disconnected.");
    bool connected = false;

    while (!connected) {
      Serial.println("Reconnecting...");
      connected = bluetooth.connect(CLIENT_NAME);  // reconnect to client
      delay(5000);                                 // time to connect
    }

    Serial.println("Connected.");
  }

  //=========================================================
  // RECEIVE BLUETOOTH DATA

  // Check for any new Bluetooth messages
  if (bluetooth.available()) {
    // Parse message from Bluetooth Serial
    String messageIn = bluetooth.readStringUntil('\n');

    // Print to Serial Monitor
    Serial.println("Received: " + messageIn);
  }

  //=========================================================
  // SEND BLUETOOTH DATA

  // Check for any new serial messages
  if (Serial.available()) {
    // Parse message from Serial Monitor
    String messageOut = Serial.readStringUntil('\n');

    // Send message
    bluetooth.println(messageOut);          // Bluetooth Serial
    Serial.println("Sent: " + messageOut);  // Serial Monitor
  }

  delay(1000);
}
