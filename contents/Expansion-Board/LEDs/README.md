# ESP32 DevKitC Expansion Board: Addressable LEDs

![](images/Thumbnail_LEDs.png)


## Contents

- [Introduction](#introduction)
- [Code](#code)

## Introduction

The ESP32 DevKitC Expansion board has four built-in addressable LEDs that we can use to display notifications, animations, or sensor data visually. The LEDs are WS2812B LEDs which are the same type of LEDs that can be found on NeoPixel products.

The LEDs are connected to the **pin 13** on the ESP32 and can be controlled using the [Adafruit NeoPixel library](https://github.com/adafruit/Adafruit_NeoPixel) which you will need to install from the Arduino IDE's Libraries Manager.


## Code

Example sketches:
- [Blink](./ESP32_ExpansionBoard_LEDBlink/ESP32_ExpansionBoard_LEDBlink.ino)
- [Chase](./ESP32_ExpansionBoard_LEDChase/ESP32_ExpansionBoard_LEDChase.ino)
- [Rainbow](./ESP32_ExpansionBoard_LEDRainbow/ESP32_ExpansionBoard_LEDRainbow.ino)

To control the onboard LEDs in out code, we will first need to include the `Adafruit_NeoPixel.h` library at the top of the sketch (make sure you have installed it first). This gives us access to the `Adafruit_NeoPixel` class that we will use to send instructions to the LEDs.

``` cpp
#include <Adafruit_NeoPixel.h>

#define LED_PIN 13 // Pin on ESP32 connected to LEDs
#define LED_NUM 4  // Number of LEDs

Adafruit_NeoPixel leds(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);
```

In the `setup()` function we need to initialise the `Adafruit_NeoPixel` object using the `begin()` method.

``` cpp
void setup() {
    leds.begin();
}
```

We then can use the range of methods provided to us by the `Adafruit_NeoPixel` class to control the LEDs colour, brightness, and position. Here are the main methods you will likely need to know how to use:

``` cpp
// Set all LEDs to "off"
leds.clear();

// Create and store colour values
// - Colours are RGB (red, green, blue) combinations
// - Setting a colour to 0 will turn it off and 255 is full brightness
// - e.g. leds.Color(255, 0, 0) means red=fully on, green=off, blue=off
uint32_t colour1 = leds.Color(255, 255, 255); // white
uint32_t colour2 = leds.Color(255, 0, 0);     // red

// Set colour of multiple LEDs at once
// Parameters: 
//  - colour value
//  - starting LED
//  - number of LEDs to fill in (from start LED) 
leds.fill(colour1, 0, LED_NUM);

// Set colour of single LED
// Parameters:
//  - LED number
//  - colour value
leds.setPixelColor(0, colour2);

// Set brightness (0-255)
leds.setBrightness(100);

// Display changes
leds.show();
```

It is important to remember that you can make as many changes to colour or brightness as you like but the LEDs won't change until you call the `show()` method.