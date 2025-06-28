//BASIC INFORMATION
// Program: monostable button
// Author:  Paweł Bartkiewicz 
// email:   15g.pawel.bart@gmail.com
//
//ADDITIONAL INFORMATION 
//
//BUTTON
// wiring diagram inside a 4-pin button
/*
      |      |
      |      |
      |--/ --|
      |      |
      |      |
*/
// pressing it closes the circuit and connects all 4 terminals

//LED DIODE
// longer LED terminal  - pin 18 (power supply)
// shorter LED terminal - GND

#define LED 18

int S = 0;

void setup() {
  pinMode(15, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {
  Z = analogRead(15);
  if(Z == LOW){
    digitalWrite(LED, HIGH);
  }
  if(Z == HIGH){
    digitalWrite(LED, LOW);
  }
}
