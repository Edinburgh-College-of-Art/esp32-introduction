//=============================================================
// File:    ESP32_Bluetooth_Client.ino
//
// Author:  J. Hathway 2025
//
// Description:
//     - This sketch will initialise the ESP32 as a Bluetooth
//       client device.
//     - Once connected to the server device, it will send and
//       receive messages over Bluetooth Serial.
//     - Use Serial Monitor to send messages to paired device.
//=============================================================

#include "BluetoothSerial.h"

BluetoothSerial bluetooth;

#define DEVICE_NAME "ESP32_Client"

//=============================================================
// SETUP

void setup() {
  // Start serial communication
  Serial.begin(115200);  // for debugging
  Serial.println();

  // Start Bluetooth Serial
  bluetooth.begin(DEVICE_NAME);
  Serial.println("The device started, ready to pair with server.");
}

//=============================================================
// LOOP

void loop() {
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