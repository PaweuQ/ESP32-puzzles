#include <Arduino.h>
#include "DHT.h"

//BASIC INFORMATION
// Program: DHT sensor setup code
// Author:  Paweł Bartkiewicz 
// email:   15g.pawel.bart@gmail.com

//ADDITIONAL INFORMATION 

// CIRCUIT
// VCC - 3.3 V
// GND - GND
// DATA - Any ESP32 pin
// 4k7 up to 10k resistor between VCC and DATA

// Libraries to install: DHT sensor library by Adafruit

// DHT settings 
#define DHTPIN 22        // GPIO pin for DTH data
#define DHTTYPE DHT11    // sensor type
DHT dht(DHTPIN, DHTTYPE); 

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {

  // the minimal difference between measurement must be higher than 1 s
  delay(2000);

  float h = dht.readHumidity();     // %
  float t = dht.readTemperature(); // default °C

  // monitoring for failures 
  if (isnan(h) || isnan(t)) {
    Serial.println(F("❌  Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h, 1);
  Serial.print(F(" %\t"));
  Serial.print(F("Temperature: "));
  Serial.print(t, 1);
  Serial.println(F(" °C"));
}
