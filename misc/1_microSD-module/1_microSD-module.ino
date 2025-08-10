//BASIC INFORMATION
// Program: microSD card module
// Author:  Paweł Bartkiewicz 
// email:   15g.pawel.bart@gmail.com
// github:  PaweuQ

//ADDITIONAL INFORMATION
// Libraries to install: OneWire and DallasTemperature

//CONNECTIONS 
// VCC - 3.3 V
// GND - GND 
// MISO - GPIO 19
// MOSI - GPIO 23
// SCK - GPIO 18
// CS - GPIO 5

// GPIO pins 19,23,18,5 are default VSPI ports for ESP32

#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>

// DS18B20 pin
#define temp 13

// microSD pins
#define SD_CS 5

OneWire oneWire(temp);
DallasTemperature sensor(&oneWire);
File dataFile;

void setup() {

  Serial.begin(9600);
  sensor.begin();
  SD.begin(SD_CS);

  if (!SD.begin(SD_CS)) {
    Serial.println("SD card initialization failed!");
    while (1);
  }
  Serial.println("SD card initialized.");

  // Create file if it doesn't exist
  if (!SD.exists("/data.csv")) {
    dataFile = SD.open("/data.csv", FILE_WRITE);
    if (dataFile) {
      dataFile.println("Temperature");
      dataFile.close();
    } else {
      Serial.println("Failed to create file!");
    }
  }
}

void loop() {
  // Request temperature from DS18B20
  sensor.requestTemperatures();
  float tempC = sensor.getTempCByIndex(0);

  // Write to CSV
  dataFile = SD.open("/data.csv", FILE_APPEND);
  if (dataFile) {
    dataFile.println(tempC);
    dataFile.close();

    Serial.print("Logged: ");
    Serial.print(tempC);
    Serial.println(" °C");
  } else {
    Serial.println("Error opening data.csv");
  }

  delay(5000);
}
