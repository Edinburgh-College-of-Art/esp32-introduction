//=============================================================
// File:    AdafruitIO_Publish_Basic.ino
//
// Author:  J. Hathway 2025
//
// Dependencies:
//     - AdafruitIO library (Adafruit)
//
// Description:
//     - Publish a random number to AdafruitIO feed
//=============================================================

#include <AdafruitIO_WiFi.h>

// Replace these parameters with your:
// - AdafruitIO username
// - AdafruitIO feed key
// - Wi-Fi network name
// - Wi-Fi password
AdafruitIO_WiFi io("aio_username", "aio_key", "wifi_name", "wifi_password");

// Replace "feed_name" with your actual feed name e.g. "Counter"
AdafruitIO_Feed *myFeed = io.feed("feed_name");


//=============================================================
// SETUP

void setup() {
  // Start serial communication
  Serial.begin(115200);
  Serial.println("AdafruitIO Publish Example");

  // Seed for random number generator
  randomSeed(analogRead(0));

  // Connect to AIO
  Serial.println("Connecting to AdafruitIO...");
  io.connect();                           // attempt connection
  while (io.status() < AIO_CONNECTED) {}  // wait until connected
  Serial.println(io.statusText());        // print connection status
}


//=============================================================
// LOOP

void loop() {
  // Generate random number
  int dataOut = random(0, 100);  // 0-99

  // Send random number to feed
  myFeed->save(dataOut);
  Serial.println("Sent: " + String(dataOut));  //print to Serial Monitor too

  // 3s delay to not exceed 30 messages per min
  delay(3000);
}