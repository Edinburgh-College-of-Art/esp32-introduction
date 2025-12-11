//=============================================================
// File:    ESP32_ExpansionBoard_LEDRainbow.ino
//
// Author:  J. Hathway 2025
//
// Dependencies:
//     - Adafruit NeoPixel library (Adafruit)
//
// Description:
//     - Run rainbow animation on onboard LEDs
//     - Code adapted from File > Examples > Adafruit_NeoPixel 
//       > strandtest
//=============================================================

#define LED_PIN 13  // Pin on ESP32 connected to LEDs
#define LED_NUM 4   // Number of LEDs on board

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel leds(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialise LEDs
  leds.begin();
  leds.show();  // Make sure LEDs are all off
}

void loop() {
  // Code adapted from File > Examples > Adafruit_NeoPixel > strandtest
  for (long hue = 0; hue < 5 * 65536; hue += 256) {
    leds.rainbow(hue);  // update rainbow() function with new hue value

    leds.setBrightness(100);  // set brightness (0-255)
    leds.show();              // display changes

    delay(10);  // short delay (10ms)
  }
}