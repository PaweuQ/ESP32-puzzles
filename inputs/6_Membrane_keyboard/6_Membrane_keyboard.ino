//INFORMACJE PODSTAWOWE
//Program: Obsluga klawiatury membranowej z 12 przyciskami 0-9 * #
//Autor: Paweł Bartkiewicz 
//mail: 15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE
// biblioteke nalezy zainstalowac
// Keypad by Mark Stanley, Alexander Brevig

//LOGIKA
// pierwsze 4 piny to rzedy 
// pozostale 3 piny to kolumny

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;

byte rowPins[ROWS] = {13, 12, 14, 27};
byte colPins[COLS] = {25, 26, 33};

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'},
};

// funkcja Keypad() przyjmuje argumenty typu char, byte, byte, byte, byte
Keypad keyboard = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  
  Serial.begin(115200);
}

void loop() {
  
  char KKey = keyboard.getKey();

  if(KKey){
    Serial.println(KKey);
  }
}
