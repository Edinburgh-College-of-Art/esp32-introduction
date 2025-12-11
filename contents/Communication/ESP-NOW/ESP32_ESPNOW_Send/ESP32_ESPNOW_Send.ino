//==============================================================
// File:    ESP32_ESPNOW_Send.ino
//
// Author:  J. Hathway 2025
//
// Description:
//     - This sketch will send ESP-NOW messages to deviced with
//       specified MAC addresses.
//     - You will need to enter the MAC address of the device(s)
//       you wish to send to.
//==============================================================

#include <WiFi.h>
#include <esp_now.h>

// Message to send
String outgoingMsg = "Hello World!";

// MAC address(es) to send to
uint8_t macAddress[] = { 0x14, 0x33, 0x5C, 0x5B, 0xA0, 0xA0 };
//uint8_t macAddress2[] = { 0x4C, 0x75, 0x25, 0x9F, 0x09, 0x28 };

// ESP-NOW variables
esp_now_peer_info_t peerInfo;
int peerCount = 0;

//=============================================================
// CALLBACK FUNCTION

// This function will be executed whenever a message is sent
void callback(const uint8_t *address, esp_now_send_status_t status) {
  // Print outgoing message to Serial Monitor
  Serial.println("\nSending message:" + outgoingMsg);

  // Check if message was delivered
  if (status != ESP_NOW_SEND_SUCCESS) {
    Serial.println("Error: Failed to deliver.");
  } else {
    Serial.println("Delivered.");
  }
}

//==============================================================
// SETUP

void setup() {
  // Start serial communication
  Serial.begin(115200);
  Serial.println("ESP-NOW Send Example");
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
  Serial.println();

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
  esp_now_register_send_cb(callback);

  //==============================================================
  // Pair Device(s)

  // Register peer
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  pair(macAddress);  // add first device
  //sendTo(macAddress2); // you would add a second device like this
}

//=============================================================
// LOOP

void loop() {
  // Send ESP-NOW message
  esp_err_t result = esp_now_send(0, (uint8_t *)&outgoingMsg, sizeof(outgoingMsg));

  // Check if message was sent successfully
  if (result != ESP_OK) {
    Serial.println("Error: Message not sent.");
  }

  // Wait 2 seconds before trying again
  delay(2000);
}

//=============================================================
// Pair a device

void pair(uint8_t *address) {
  peerCount++;

  // Add peer device
  memcpy(peerInfo.peer_addr, address, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Error: Failed to add peer " + String(peerCount));
  }
}
