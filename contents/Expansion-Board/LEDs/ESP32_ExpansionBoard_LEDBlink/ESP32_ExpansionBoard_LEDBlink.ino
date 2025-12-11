//=============================================================
// File:    ESP32_ExpansionBoard_LEDBlink.ino
//
// Author:  J. Hathway 2025
//
// Dependencies:
//     - Adafruit NeoPixel library (Adafruit)
//
// Description:
//     - Blink on board LEDs red, green and blue changing once
//       every second.
//=============================================================

#define LED_PIN 13  // Pin on ESP32 connected to LEDs
#define LED_NUM 4   // Number of LEDs on board

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel leds(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);

// Create and store colour values
uint32_t red = leds.Color(255, 0, 0);
uint32_t grn = leds.Color(0, 255, 0);
uint32_t blu = leds.Color(0, 0, 255);

// Brightness value (0-255)
int brightness = 100;

void setup() {
  // Initialise LEDs
  leds.begin();
  leds.show();  // Make sure LEDs are all off
}

void loop() {
  // RED
  leds.fill(red, 0, LED_NUM);      // set all LEDs to red
  leds.setBrightness(brightness);  // set brightness
  leds.show();                     // display changes
  delay(1000);                     // wait for 1 second

  // GREEN
  leds.fill(grn, 0, LED_NUM);  // set all LEDs to green
  leds.setBrightness(brightness);
  leds.show();
  delay(1000);

  // BLUE
  leds.fill(blu, 0, LED_NUM);  // set all LEDs to blue
  leds.setBrightness(brightness);
  leds.show();
  delay(1000);
}