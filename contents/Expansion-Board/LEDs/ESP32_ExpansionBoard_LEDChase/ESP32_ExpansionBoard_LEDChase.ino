//=============================================================
// File:    ESP32_ExpansionBoard_LEDChase.ino
//
// Author:  J. Hathway 2025
//
// Dependencies:
//     - Adafruit NeoPixel library (Adafruit)
//
// Description:
//     - Animate a pixel chase using the onboard LEDs
//=============================================================

#define LED_PIN 13  // Pin on ESP32 connected to LEDs
#define LED_NUM 4   // Number of LEDs on board

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel leds(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);

// Create and store colour value
uint32_t white = leds.Color(255, 255, 255);

// Brightness value (0-255)
int brightness = 100;

void setup() {
  // Initialise LEDs
  leds.begin();
  leds.show();  // Make sure LEDs are all off
}

void loop() {
  // Cycle through all LEDs 0-3
  for (int i = 0; i < LED_NUM; i++) {
    leds.clear();  // clear current colours

    leds.setPixelColor(i, white);    // turn on next led
    leds.setBrightness(brightness);  // set brightness
    leds.show();                     // display changes

    delay(200);  // short elay (200ms)
  }
}