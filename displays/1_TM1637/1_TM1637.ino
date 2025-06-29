//INFORMACJE PODSTAWOWE
//Program: Obsluga 4-cyfrowego wyswietlacza TM1637
//Autor: Paweł Bartkiewicz 
//mail: 15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE
//biblioteke TM1637 nalezy pobrac

//PODLACZENIE
// CLK - 32
// DIO - 33
// 3.3 V

#include <TM1637Display.h>

// definiowanie obiektu wyswietlacza
#define CLK_PIN 32  // pin zegarowy
#define DIO_PIN 33  // pin danych
TM1637Display display(CLK_PIN, DIO_PIN);

void setup() {
  
  Serial.begin(115200);
  
  display.setBrightness(1); // ustaw jasnosc (0-7)
  display.clear();
}

void loop() {
  
  //number = 21;
  //display.showNumberDec(number);

  String X = "342";
  int number = X.toInt();  
  display.showNumberDec(number);  
}
