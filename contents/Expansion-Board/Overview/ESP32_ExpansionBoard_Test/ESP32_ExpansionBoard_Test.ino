//=============================================================
// File:    ESP32_ExpansionBoard_Test.ino
//
// Author:  J. Hathway 2025
//
// Description:
//     - Test sketch for all onboard components on ESP32
//       expansion board.
//=============================================================

// Pin definitions
#define BUTTON_PIN_0 14  // Button 0
#define BUTTON_PIN_1 27  // Button 1
#define BUTTON_PIN_2 26  // Button 2
#define BUTTON_PIN_3 25  // Button 3
#define POT_PIN 32       // Potentiometer
#define LED_PIN 13       // LEDs
#define SERVO_PIN 12     // Servo

// Other starting parameters
#define BUTTON_NUM 4        // Number of buttons on board
#define LED_NUM 4           // Number of LEDs on board
#define LED_BRIGHTNESS 100  // Maximum LED brightness

//==============================================================
// LIBRARIES

#include <Adafruit_NeoPixel.h>
#include <ESP32Servo.h>

//==============================================================
// GLOBAL VARIABLES

Adafruit_NeoPixel leds(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);
Servo servo;

int potValue = 0;
int servoValue = 0;
int ledVals[LED_NUM] = { 0, 1, 2, 3 };
int buttonVals[BUTTON_NUM] = { 0, 0, 0, 0 };
int buttonPins[BUTTON_NUM] = { BUTTON_PIN_0, BUTTON_PIN_1, BUTTON_PIN_2, BUTTON_PIN_3 };

//==============================================================
// COLOURS

// Get/store hex values for chosen colours
const uint32_t C_VALUES[LED_NUM] = {
  Adafruit_NeoPixel::Color(255, 0, 0),     // Red
  Adafruit_NeoPixel::Color(0, 255, 0),     // Green
  Adafruit_NeoPixel::Color(0, 0, 255),     // Blue
  Adafruit_NeoPixel::Color(255, 255, 255)  // White
};

// Colour labels for debugging
const String C_LABELS[LED_NUM] = {
  "RED",
  "GRN",
  "BLU",
  "WHI",
};

//==============================================================
// SETUP

void setup() {
  // Start serial communication
  Serial.begin(115200);
  Serial.println("ESP32 Expansion Board Test");

  // Initialise pullup pins
  pinMode(BUTTON_PIN_0, INPUT_PULLUP);
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);

  // Initialise LED object
  leds.begin();
  leds.show();  // turn off any LEDs currently on

  // Initialise servo object
  servo.attach(SERVO_PIN);
}

//==============================================================
// LOOP

void loop() {
  updateButtons();
  updatePotentiometer();

  setLEDs();
  setServo();

  printData();
}

//==============================================================
// BUTTONS

/// Use buttons to update LED colour values
void updateButtons() {
  // Iterate through all buttons
  for (int i = 0; i < BUTTON_NUM; i++) {
    // Get button value
    int currentValue = digitalRead(buttonPins[i]);

    // If button value changed AND equals 0...
    if (buttonVals[i] != currentValue && currentValue == 0) {
      ledVals[i] = (ledVals[i] + 1) % 4;  // ...increment led value but keep between 0-3
    }

    // Update button value
    buttonVals[i] = currentValue;
  }
}

//==============================================================
// POTENTIOMETER

/// Get potentiometer value
void updatePotentiometer() {
  potValue = analogRead(POT_PIN);
}

//==============================================================
// LEDS

/// Set LED colours according to colour values
void setLEDs() {
  // Iterate through all LEDs
  for (int i = 0; i < LED_NUM; i++) {
    leds.setPixelColor(i, C_VALUES[ledVals[i]]);  // set pixel colour according to LED colour value
  }

  // Display changes
  leds.setBrightness(LED_BRIGHTNESS);  // adjust brightness
  leds.show();
}

//==============================================================
// SERVO

/// Set servo position according to potentiometer value
void setServo() {
  // Scale input range from 0-4095 to 0-180
  servoValue = map(potValue, 0, 4095, 0, 180);

  // Set servo angle
  servo.write(servoValue);
}

//==============================================================
// PRINT DATA

/// Print all values to Serial Monitor
void printData() {
  Serial.print("Buttons: ");
  Serial.print(buttonVals[0]);
  Serial.print(", ");
  Serial.print(buttonVals[1]);
  Serial.print(", ");
  Serial.print(buttonVals[2]);
  Serial.print(", ");
  Serial.print(buttonVals[3]);

  Serial.print("\tColours: ");
  Serial.print(C_LABELS[ledVals[0]]);
  Serial.print(", ");
  Serial.print(C_LABELS[ledVals[1]]);
  Serial.print(", ");
  Serial.print(C_LABELS[ledVals[2]]);
  Serial.print(", ");
  Serial.print(C_LABELS[ledVals[3]]);

  Serial.print("\tPotentiometer: ");
  Serial.print(potValue);

  Serial.print("\tServo: ");
  Serial.print(servoValue);

  Serial.println();
}
