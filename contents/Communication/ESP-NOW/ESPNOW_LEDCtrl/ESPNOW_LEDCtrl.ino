//================================================================
// File:    ESPNOW_LEDCtrl.ino
//
// Author:  J. Hathway 2026
//
// Description:
//     - Use potentiometer to control LED colour on paired device.
//     - Paired device can control colour of LEDs on this device.
//================================================================

#include <Adafruit_NeoPixel.h>

#include <WiFi.h>
#include <esp_now.h>

#define LED_PIN 13  // Pin connected to LEDs
#define POT_PIN 32  // Pin connected to potentiometer

// MAC address of other device
uint8_t macAddress[] = { 0x38, 0x18, 0x2B, 0xF7, 0xC0, 0x2C };

//==============================================================
// GLOBAL VARIABLES

// ESP-NOW variables
esp_now_peer_info_t peerInfo;
int peerCount = 0;

// Variable to store in/out messages
String outgoingVal;
String incomingVal;

// NeoPixel setup
#define LED_NUM 4           // Number of LEDs on board
#define LED_BRIGHTNESS 100  // Maximum brightness
Adafruit_NeoPixel leds(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);

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
  // NeoPixel
  leds.begin();
  leds.clear();
  leds.show();
}

//=============================================================
// LOOP

void loop() {
  //==============================================================
  // Get/Send Potentiomter Value

  // Read potentiometer value
  outgoingVal = String(analogRead(POT_PIN));

  // Send potentiometer value to paired device
  esp_err_t result = esp_now_send(0, (uint8_t *)&outgoingVal, sizeof(outgoingVal));

  // Check if message was sent successfully
  if (result != ESP_OK) {
    Serial.println("Error: Message not sent.");
  }

  //==============================================================
  // Update LEDs from Incoming Value

  int ledValue = map(incomingVal.toInt(), 0, 4095, 0, 765);

  uint32_t colour = 0;

  if (ledValue <= 255) {
    colour = leds.Color(255 - ledValue, ledValue, 0);
  } else if (ledValue <= 510) {
    ledValue -= 255;
    colour = leds.Color(0, 255 - ledValue, ledValue);
  } else {
    ledValue -= 510;
    colour = leds.Color(ledValue, 0, 255 - ledValue);
  }

  leds.fill(colour, 0, LED_NUM);
  leds.setBrightness(LED_BRIGHTNESS);
  leds.show();

  //==============================================================
  // Print values to Serial Monitor

  Serial.print("In: " + incomingVal);
  Serial.print(", Out:" + outgoingVal);
  Serial.println();

  delay(100);
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
