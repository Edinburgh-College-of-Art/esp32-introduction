//=============================================================
// File:    AdafruitIO_Subscribe.ino
//
// Author:  J. Hathway 2025
//
// Dependencies:
//     - AdafruitIO library (Adafruit)
//
// Description:
//     - Subscribe data from AdafruitIO feed
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
// CALLBACK FUNCTION

void handleMessage(AdafruitIO_Data *data) {
  // Receive incoming data
  String incomingData = data->value();

  // print incoming data to Serial Monitor
  Serial.print("Received: ");
  Serial.println(incomingData);
}

//=============================================================
// SETUP

void setup() {
  // Start serial communication
  Serial.begin(115200);
  Serial.println("AdafruitIO Subscribe Example");

  // Connect to AIO
  Serial.println("Connecting to AdafruitIO...");
  io.connect();                           // attempt connection
  while (io.status() < AIO_CONNECTED) {}  // wait until connected
  Serial.println(io.statusText());        // print connection status

  // Pin callback function to message received
  myFeed->onMessage(handleMessage);
  myFeed->get();
}


//=============================================================
// LOOP

void loop() {
  io.run();
}