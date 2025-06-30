//BASIC INFORMATION
// Program: QT18B20 temperature sensor setup code
// Author:  Paweł Bartkiewicz 
// email:   15g.pawel.bart@gmail.com
// github:  PaweuQ

//ADDITIONAL INFORMATION 

// CIRCUIT
// VCC - 3.3 V
// DQ - Any ESP32 GPIO pin (middle pin)
// GND - GND (left pin, when you look at the flat surface of the sensor)
// 4k7 up to 10k resistor between VCC and DQ

// Libraries to install: OneWire and DallasTemperature

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire one(23);
DallasTemperature sensor(&one);
float SensorOutcome = 0;
   
void setup() {
  Serial.begin(115200);
  sensor.begin();
}

void loop() {

  delay(2000);
  sensor.requestTemperatures();
  SensorOutcome = sensor.getTempCByIndex(0);

  Serial.print("Temperature: ");
  Serial.print(SensorOutcome);
  Serial.println("°C");
}