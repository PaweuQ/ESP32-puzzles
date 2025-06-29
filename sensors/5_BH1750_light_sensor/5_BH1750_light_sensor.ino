//INFORMACJE PODSTAWOWE
//Program: Czujnik natezenia swiatla BH1750
//Autor: Paweł Bartkiewicz 
//mail: 15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE
// Biblioteke BH1750 nalezy zainstalowac
// BH1750 by Christopher Laws 

// Czujnik BH1750 mierzy natezenie swiatla w luxach 

//PODLACZENIE 
// zasilanie 3.3 V
// SCL do 21
// SDA (DAT) do 22
// ADDR nie podlaczac

// czujnik korzysta z interfejsu I2C
// piny 21 i 22 to domyslne piny I2C w ESP32

#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter(0x23);

void setup() {
  
  Serial.begin(115200);

  // (SDA, SCL)
  Wire.begin(22, 21);
  lightMeter.begin();
}

void loop() {
  
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
}
