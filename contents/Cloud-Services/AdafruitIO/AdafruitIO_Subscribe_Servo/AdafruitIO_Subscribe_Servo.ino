//=============================================================
// File:    AdafruitIO_Subscribe_Servo.ino
//
// Author:  J. Hathway 2026
//
// Dependencies:
//     - AdafruitIO library (Adafruit)
//
// Description:
//     - Subscribe potentiometer data from AIO and use it to 
//       update servo position.
//=============================================================

#include <AdafruitIO_WiFi.h>
#include <ESP32Servo.h>

#define SERVO_PIN 12

// Replace these parameters with your:
// - AdafruitIO username
// - AdafruitIO feed key
// - Wi-Fi network name
// - Wi-Fi password
AdafruitIO_WiFi io("aio_username", "aio_key", "wifi_name", "wifi_password");

// Replace "feed_name" with your actual feed name e.g. "Counter"
AdafruitIO_Feed *myFeed = io.feed("feed_name");

// Servo object
Servo servo;

//=============================================================
// CALLBACK FUNCTION

void handleMessage(AdafruitIO_Data *data) {
  // Receive incoming data
  String incomingData = data->value();

  // Scale data from 0-4095 to 0-180
  int servoPosition = map(incomingData.toInt(), 0, 4095, 0, 180);

  // Update servo position
  servo.write(servoPosition);

  // Print data to Serial Monitor
  Serial.print("Received: ");
  Serial.print(incomingData);
  Serial.print(", Servo position: ");
  Serial.print(servoPosition);
  Serial.println();
}

//=============================================================
// SETUP

void setup() {
  // Start serial communication
  Serial.begin(115200);
  Serial.println("AdafruitIO Servo Example");

  // Connect to AIO
  Serial.println("Connecting to AdafruitIO...");
  io.connect();                           // attempt connection
  while (io.status() < AIO_CONNECTED) {}  // wait until connected
  Serial.println(io.statusText());        // print connection status

  // Pin callback function to message received
  myFeed->onMessage(handleMessage);
  myFeed->get();

  // Attach pin to servo object
  servo.attach(SERVO_PIN);
}


//=============================================================
// LOOP

void loop() {
  io.run();
}