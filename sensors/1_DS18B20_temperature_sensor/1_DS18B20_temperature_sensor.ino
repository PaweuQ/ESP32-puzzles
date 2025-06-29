//INFORMACJE PODSTAWOWE
//Program: Czujnik temperatury DS18B20
//Autor: Paweł Bartkiewicz 
//mail: 15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE 
//Biblioteki OneWire i DallasTemperature nalezy pobrac

//lewe     wyprowadzenie - GND
//srodkowe wyprowadzenie - pin 23 na esp32
//prawe    wyprowadzenie - 3.3V lub 5V
//rezystor 4.7 k - mostek pomiedzy prawym a srodkowym 

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
  sensor.requestTemperatures();
  SensorOutcome = sensor.getTempCByIndex(0);

  Serial.print("Temperatura: ");
  Serial.print(SensorOutcome);
  Serial.println("°C");
}
