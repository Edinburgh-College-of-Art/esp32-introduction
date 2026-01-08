//================================================================
// File:    ESPNOW_ServoCtrl.ino
//
// Author:  J. Hathway 2026
//
// Description:
//     - Use potentiometer to control servo on paired device.
//     - Paired device can control servo on this device.
//================================================================

#include <ESP32Servo.h>

#include <WiFi.h>
#include <esp_now.h>

#define SERVO_PIN 12  // Pin connected to servo
#define POT_PIN 32    // Pin connected to potentiometer

// MAC address of other device
uint8_t macAddress[] = { 0x38, 0x18, 0x2B, 0xF8, 0xB8, 0xA0 };

//==============================================================
// GLOBAL VARIABLES

// ESP-NOW variables
esp_now_peer_info_t peerInfo;
int peerCount = 0;

// Variable to store in/out messages
String outgoingVal;
String incomingVal;

// Servo Object
Servo servo;

//==============================================================
// SETUP

void setup() {
  // Start serial communication
  Serial.begin(115200);
  Serial.println("ESP-NOW LED Example");
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

  //==============================================================
  // Servo setup

  // Attach pin to servo object
  servo.attach(SERVO_PIN);
}

//=============================================================
// LOOP

void loop() {
  //==============================================================
  // Get/Send potentiomter value

  // Read potentiometer value
  outgoingVal = String(analogRead(POT_PIN));

  // Send potentiometer value to paired device
  esp_err_t result = esp_now_send(0, (uint8_t *)&outgoingVal, sizeof(outgoingVal));

  // Check if message was sent successfully
  if (result != ESP_OK) {
    Serial.println("Error: Message not sent.");
  }

  //==============================================================
  // Update servo position from Incoming Value

  // Scale incoming data from 0-4095 to 0-180
  int servoPosition = map(incomingVal.toInt(), 0, 4095, 0, 180);

  // Update servo position
  servo.write(servoPosition);

  //==============================================================
  // Print values to Serial Monitor

  Serial.print("Out: " + outgoingVal);
  Serial.print(", In: " + incomingVal);
  Serial.print(", Servo position: " + String(servoPosition));
  Serial.println();
}

//=============================================================
// CALLBACK FUNCTIONS

// This function is executed when message is received
void messageReceived(const uint8_t *address, const uint8_t *incomingData, int length) {
  incomingVal = "";

  // Copy incoming data to message variable
  for (int i = 0; i < length; i++) {
    // If end of strink, break loop
    if ((char)incomingData[i] == '\0') break;

    incomingVal += (char)incomingData[i];
  }
}

// This function will be executed whenever a message is sent
void messageSent(const uint8_t *address, esp_now_send_status_t status) {
  // Check if message was delivered
  if (status != ESP_NOW_SEND_SUCCESS) {
    Serial.println("Error: Failed to deliver.");
  }
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
