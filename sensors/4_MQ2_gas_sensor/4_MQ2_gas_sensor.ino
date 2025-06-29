//INFORMACJE PODSTAWOWE
//Program: Obsluga czujnika gazow latwopalnych MQ2 (Flying-Fish)
//Autor: Paweł Bartkiewicz 
//mail: 15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE
//zasilanie 5 V
//A0 do pinu 34
//czujnik testowany na gazie z zapalniczki

#include <Wire.h>
#define sensor 34

void setup(){

  Serial.begin(115200);
}

void loop(){

  GASLevel();
  delay(1000);
}

void GASLevel(){
  
  int value = analogRead(sensor);
  value = map(value, 0, 4095, 0, 100);

  if (value >= 50) {
    Serial.println("danger");
  } else {
    Serial.println("NOT danger");
  }
}
