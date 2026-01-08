# API Requests on an ESP32

![](images/Thumbnail_APIs.png)

## Contents

- [Introduction](#introduction)
    - [What are APIs](#what-are-apis)
    - [How API Requests Work](#how-api-requests-work)
        - [Making a Request](#making-a-request)
        - [Getting a Response](#getting-a-response)
        - [Deserializing the Response](#deserializing-the-response)
    - [Arduino JSON Assistant](#arduino-json-assistant)
        - [Installing the Arduino JSON Library](#installing-the-arduino-json-library)
        - [Generating the Code](#generating-the-code)
- [Usage](#usage)
    - [Making the Request](#making-the-request)
    - [Deserializing the response](#deserializing-the-response-1)

## Introduction

### What are APIs?

APIs, or Application Programming Interfaces, are like bridges that let different devices and software talk to each other. In IoT projects, APIs allow your projects to send and receive data over the internet. Instead of building everything from scratch, you can use APIs to connect your devices to external services, such as cloud storage, data gathering, or mobile apps. 

An easy way to think of an API is as a computer/server somewhere in the world that you can access using a specific URL. Depending on the contents of the URL, you can send a request to the server to retrieve some information or perform some action. The server will then send you a response with either the information you have requested, or a confirmation telling you whether it has performed the requested action.

For example, if your ESP32 needed to know what the weather in Paris is currently, without an API you may have to create your own weather station, set it up in Paris, and figure out a way to send the weather data back to your ESP32. Luckily, we can instead find a suitable API that provides live weather data and pull the data from that.

You can find an extensive list of free and public APIs [here](https://github.com/public-apis/public-apis?tab=readme-ov-file).


### How API Requests work

#### Making a Request

There are a couple of different requests we can make using HTTP and HTTPS, including **GET**, **POST**, **PUT**, and **DELETE**.  Each of these requests will ask the server to do something different. For example:

- **GET** - ask the server to retrieve some data.
- **POST** - send data to a server to create a new resource.
- **PUT** - update an existing resource with new data.
- **DELETE** - remove a specified resource from the server.
 
Some APIs require API keys for authentication. This is a specific key/password/token that an API provider will give to authorised parties to include in their requests, in order to prove to the server that they have access to the API. 

A typical request URL might look something like this:

`https://api.example.com/v1/users?status=active&sort=desc&api_key=YOUR_API_KEY`

This includes:

1. **Protocol:** *“https://”* - Specifies secure communication using HTTPS.
2. **Base URL (Domain):** *“api.example.com”* - The domain where the API is hosted.
3. **Endpoint:** *“/v1/users”* - Indicates the version of the API and the specific resource.
4. **Query Parameters:**
    - *“status=active”* - Filter the results based on a parameter called “active”.
    - *"sort=desc”* - Sort the results in descending order.
    - *“api_key=YOUR_API_KEY”* - The API key included as a query parameter for authentication.

It is important to remember, however, that each API will have its own way of making requests, so it is important to read the API documentation to understand how it works before attempting to use it in your projects.


#### Getting a Response

As previously mentioned, making an API request essentially consists of searching for a specific URL to retrieve data or trigger an action at the server end. As such, we can do this from a browser on your computer. The following URL makes a request to the [Open-Meteo API](https://open-meteo.com/) for information on the current temperature in Edinburgh. Copy this URL and paste it in your browser's address bar:

`https://api.open-meteo.com/v1/forecast?latitude=55.9521&longitude=-3.1965&current=temperature_2m`

This should take you to an empty site with some text that looks something like this:

``` js
{"latitude":55.96,"longitude":-3.2,"generationtime_ms":0.013947486877441406,"utc_offset_seconds":0,"timezone":"GMT","timezone_abbreviation":"GMT","elevation":74.0,"current_units":{"time":"iso8601","interval":"seconds","temperature_2m":"°C"},"current":{"time":"2024-05-29T09:45","interval":900,"temperature_2m":16.4}}
```

This is the API response to our request. If successful, the API will send the client a response that either includes the requested information, or a confirmation of whether or not it has successfully performed the requested action.

In this example, you may be able to see that within this response is the information we requested: the current temperature in Edinburgh. It may be tricky to find due to the format of the response. This format is called JavaScript Object Notation (JSON) and is the typical format of API responses. 

By tidying up the JSON response, we can more easily see the information given to us:

``` js
{
  "latitude": 55.96,
  "longitude": -3.2,
  "generationtime_ms": 0.0139474868774414,
  "utc_offset_seconds": 0,
  "timezone": "GMT",
  "timezone_abbreviation": "GMT",
  "elevation": 74,
  "current_units": {
    "time": "iso8601",
    "interval": "seconds",
    "temperature_2m": "°C"
  },
  "current": {
    "time": "2024-05-29T09:45",
    "interval": 900,
    "temperature_2m": 16.4
  }
}
```

Hopefully you can find in this request that the temperature is 16.4 degrees. This will probably be different when you make your request, as this API provides up-to-date weather information.


#### Deserializing the Response

When a IoT device - such as an ESP32 - makes an API request, it will have to decode the JSON response to find and extract the relevant data from it in a process called “deserializing”.

In the above example, you can see that the response is separated into nested “objects” enclosed in curly brackets {}. Within these objects are a series of key-value pairs, which give us the type of information and its value. 

For example, you can see the latitude and longitude values in the main object:

``` js
{
  "latitude": 55.96,
  "longitude": -3.2,
   ...
}
```

But to find the current temperature, you have to into a nested object called `current` where you can find the key `temperature_2m` with the value `16.4`:

``` js
{
  ...,
  
  "current": {
    "time": "2024-05-29T09:45",
    "interval": 900,
    "temperature_2m": 16.4
  }
}
```

To use the information stored in an API response, your ESP32 code will need to know:

1. What the expected response will look like.
2. How to deserialize the expected response.


### Arduino JSON Assistant

There exists an Arduino library and web tool for automatically generating the code required for deserializing JSON responses. The [Arduino JSON library](https://github.com/bblanchon/ArduinoJson) and [Arduino JSON assistant](https://arduinojson.org/v7/assistant/#/step1) were created by Benoît Blanchon for the specific purpose of making the Arduino code for deserializing JSON files simpler and more readable. 

In this section, we will look at how to use the Arduino JSON assistant to generate code for deserializing the Open-Meteo API response from the previous section.


#### Installing the Arduino JSON Library
To make use of the auto-generated code in our sketches/projects, we need to install Benoît Blanchon's Arduino JSON library from your IDE of choice.

![](images/ArduinoJson_Library.png)


#### Generating the Code
To generate the code for deserializing a JSON response, you can first navigate to the [Arduino JSON Assistant 7](https://arduinojson.org/v7/assistant/#/step1). From there, follow these steps:

1. **Configuration**

The first step requires inputting some configuration information. For an ESP32, make sure you have selected:

- Board = DOIT ESP32 DEVKIT V1
- Mode = Deserialize
- Input = Stream

![](images/ArduinoJson_Configuration.png)

After this, click *Next: JSON*.

2. **JSON**

`https://api.open-meteo.com/v1/forecast?latitude=55.9521&longitude=-3.1965&current=temperature_2m`

Copy the request URL into your browser's address bar, press enter, and copy the JSON response to your clipboard. For this example, we will use the above request URL and subsequent response, however, for your own projects you should use the API URL that you intend to use.

You can then paste the example response into the text box marked Input in the JSON Assistant. Optionally, you can press the icon on the bottom-right of the text box to tidy up the JSON into a prettier format.

![](images/ArduinoJson_JSON.png)

After this, click *Next: Program* to continue to the next page.

3. **Program**
You should now see on this page, generated code for deserializing a JSON response on your ESP32. 

![](images/ArduinoJson_Program.png)

You can now copy and paste this code into your own sketch to use. You will need to make sure that you have first programmed to the ESP32 to make an API request and receive the response. 

In the following sections we will look at how to get an JSON response from an API and how to deserialize it from the ESP32. 

## Usage

For a full example sketch, [click here](API_OpenMeteo/API_OpenMeteo.ino).

To make and deserialize an API request from the ESP32, we will need to include the:

- **WiFi Library** - for connecting to the internet.
- **HTTP Client Library** - for making the HTTP request.
- **Arduino JSON Library** - for deserializing the response.

It is also worth storing the Wi-Fi credentials and API url as variables to use later in the sketch.

``` cpp
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
  
//=======================================================
// **REPLACE THESE VARIABLES WITH YOUR DETAILS**
const char* ssid = "YourNetwork";
const char* password = "YourPassword";

// API Request URL
const char* requestURL = "https://api.example.com/v1/";
//=======================================================
```

To make an API request, the ESP32 will first need to connect to the internet via a Wi-Fi connection. We will not look at how this works here, but if you want to find out more, [click here](/examples/Wireless-Communication/Wi-Fi/README.md).

### Making the Request
To make an API request, we will need to create and initialise an instance of the `HTTPClient` object.

``` cpp
// Make API Request
HTTPClient client;
client.begin(requestURL);
```

We will then need to check if we have successfully received a response from the API. We will use a `while()` loop to make sure we don't continue if not.

``` cpp
// Get status
int status = client.GET();
​
if (status == 0) {
  Serial.println("Connection failed");
  while (true) {} // do not continue if connection has failed
}
```

After making sure that we have received a successful response from the API, we can save the JSON response as a string variable and end the HTTP connection. 

``` cpp
// Retrieve JSON response
String payload = client.getString();
client.end();  // End HTTP connection
```

If successful, the API response now be stored in the `payload` variable, ready to be deserialized.

### Deserializing the Response
To deserialize the response from the API, we can use the classes and functions given to us by the Arduino JSON library, and the code generated by the Arduino JSON assistant.

First of all, you will need to follow the steps laid out [here](#generating-the-code) to get the generated code from the Arduino JSON assistant. You should then be able to past it into your code with a few alterations:

- Pass the variable containing the response into the `deserializeJson()` function in place of the `input` variable.
- Quite often an API response will give you time/date data along with some other things that we are not necessarily interested in. You can trim down the code so it only retrieves the data you need.

The end result should look something like this:

``` cpp
// Deserialize JSON
JsonDocument doc;
DeserializationError error = deserializeJson(doc, payload);
  
if (error) {
  Serial.print("deserializeJson() failed: ");
  Serial.println(error.c_str());
  while (true) {}
}
  
// Retrieve data
JsonObject current = doc["current"];
  
float current_temperature_2m = current["temperature_2m"];  // temperature
float current_rain = current["rain"];                      // rain
float current_pressure_msl = current["pressure_msl"];      // pressure
```

You should now be able to use the deserialized data in the rest of your code.
