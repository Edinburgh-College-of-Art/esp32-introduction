//==============================================================
// File:    ESPNOW_SendReceive.ino
//
// Author:  J. Hathway 2026
//
// Description:
//     - This sketch will send ESP-NOW messages to deviced with
//       specified MAC addresses.
//     - This sketch will also receive any incoming ESP-NOW 
//       messages and print them to the Serial Monitor.
//     - You will need to enter the MAC address of the device(s)
//       you wish to send to.
//==============================================================

#include <WiFi.h>
#include <esp_now.h>

// Variable to store in/out messages
String outgoingMsg = "Hello"; // feel free to replace this with your own message
String incomingMsg;

// MAC address of other device
uint8_t macAddress[] = { 0x38, 0x18, 0x2B, 0xF7, 0xC0, 0x2C };

// ESP-NOW variables
esp_now_peer_info_t peerInfo;
int peerCount = 0;

//=============================================================
// CALLBACK FUNCTIONS

// This function is executed when message is received
void messageReceived(const uint8_t *address, const uint8_t *incomingData, int length) {
  // Clear string variable
  incomingMsg = "";

  // Copy incoming data to message variable
  for (int i = 0; i < length; i++) {
    // If end of strink, break loop
    if ((char)incomingData[i] == '\0') break;

    incomingMsg += (char)incomingData[i];
  }

  // Print message to Serial Monitor
  Serial.println("\nReceived: " + incomingMsg);
}

// This function will be executed whenever a message is sent
void messageSent(const uint8_t *address, esp_now_send_status_t status) {
  // Print outgoing message to Serial Monitor
  Serial.println("\nSending message:" + outgoingMsg);

  // Check if message was delivered
  if (status != ESP_NOW_SEND_SUCCESS) {
    Serial.println("Error: Failed to deliver.");
  }
}

//==============================================================
// SETUP

void setup() {
  // Start serial communication
  Serial.begin(115200);
  Serial.println("ESP-NOW Send and Receive Example");
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

  // Pin callback functions
  esp_now_register_send_cb(messageSent);      // on message sent
  esp_now_register_recv_cb(messageReceived);  // on message received

  //==============================================================
  // Pair Device(s)

  // Register peer
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  pair(macAddress);  // add first device
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
