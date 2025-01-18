#include <ESP8266WiFi.h>
#include <Ubidots.h>

// Wi-Fi credentials
const char* WIFI_SSID = "CSE CLASS ROOM";
const char* WIFI_PASSWORD;

// Ubidots credentials
#define TOKEN "BBUS-fb16LFCQf6I7Z4P5MqrrJ5nZGph6Ba"  // Replace with your Ubidots token
#define DEVICE_LABEL "DHT11"  // Label for your device in Ubidots
#define VARIABLE_LABEL "Temperature"  // Label for your variable in Ubidots
Ubidots ubidots(TOKEN);

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected.");
}

void loop() {
  int myValue = 42;  // Integer to send to Ubidots
  Serial.println("Sending data to Ubidots...");
  
  // Add variable and send the value
  ubidots.add(VARIABLE_LABEL, myValue);  // Add the value (no need to check return)
  myValue = 44;
  ubidots.add(VARIABLE_LABEL, myValue);  
  myValue = 46;
  ubidots.add(VARIABLE_LABEL, myValue); 

  // Send the data to Ubidots
  if (ubidots.send(DEVICE_LABEL)) {        
    Serial.println("Data sent successfully.");
  } else {
    Serial.println("Failed to send data.");
  }

  delay(5000); // Wait 5 seconds before sending again
}