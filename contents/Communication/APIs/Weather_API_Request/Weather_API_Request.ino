//=============================================================
// File:    API_ExampleRequest.ino
//
// Author:  J. Hathway 2025
//
// Dependencies:
//     - Arduino JSON library (Benoît Blanchon)
//
// Description:
//     - This sketch makes an example API request from an
//       ESP32 using the https://open-meteo.com/ API.
//     - This sketch will then deserialize the response to
//       retrieve temperature, rainfall, and air pressure data
//       and print it to the Serial Monitor.
//     - You will need to replace the ssid and password
//       variables with your own Wi-Fi network name and
//       password.
//=============================================================

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//=======================================================
// **REPLACE THESE VARIABLES WITH YOUR DETAILS**
const char* ssid = "WiFiNetworkName";
const char* password = "WiFiNetworkPassword";
//=======================================================

// API Request URL
const char* requestURL = "https://api.open-meteo.com/v1/forecast?latitude=55.9521&longitude=-3.1965&current=temperature_2m,rain,pressure_msl";

// Function definitions
bool connectToWiFi(const char* _ssid, const char* _password);

//=======================================================
// SETUP

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  // Do not continue if not connected
  while (!connectToWiFi(ssid, password)) {}
}


//=======================================================
// LOOP

void loop() {
  //=======================================================
  // 1. MAKE REQUEST

  // Get JSON response
  String payload;  // this will store the entire response
  makeAPIRequest(payload);

  //=======================================================
  // 2. DESERIALIZE RESPONSE

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    while (true) {}
  }

  //=======================================================
  // 3. EXTRACT DATA

  JsonObject current = doc["current"];

  float temperature = current["temperature_2m"];  // temperature in celsius
  float rain = current["rain"];                   // rain in mm
  float pressure = current["pressure_msl"];       // air pressure in hPa
  
  //=======================================================
  // 4. USE/PRINT DATA

  // Print data to Serial Monitor
  Serial.println("Temp: " + String(temperature) + "C");
  Serial.println("Rain: " + String(rain) + "mm");
  Serial.println("Pres: " + String(pressure) + "hPa");

  //=======================================================

  // Wait 1 min before making next request
  delay(60000);
}

//============================================================
// Make API Request

void makeAPIRequest(String& _payload) {
  // Start HTTP client
  HTTPClient client;
  client.begin(requestURL);

  // Get status
  int status = client.GET();

  if (status == 0) {
    Serial.println("Connection failed");
    while (true) {}
  }

  // Retrieve JSON response
  _payload = client.getString();
  client.end();  // End HTTP connection
}

//============================================================
// Connect to WiFi

bool connectToWiFi(const char* _ssid, const char* _password) {
  Serial.println("Connecting to:");
  Serial.println(_ssid);

  // Start connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);
  unsigned long startAttemptTime = millis();

  // Wait until connected, or timed out
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 30000) {
    Serial.print(".");
    delay(400);
  }

  Serial.println();

  // Print connection status
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Err: Failed to connect");
    delay(2000);
    return false;
  } else {
    Serial.println("Connected");
    delay(2000);
    return true;
  }
}