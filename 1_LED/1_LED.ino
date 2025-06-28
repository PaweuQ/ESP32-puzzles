//BASIC INFORMATION
// Program: simple diode blinking 
// Author:  Paweł Bartkiewicz 
// email:   15g.pawel.bart@gmail.com

//ADDITIONAL INFORMATION 
// longer diode pin  - pin 15 (power supply)
// shorter diode pin - GND

void setup() {
  pinMode(15, OUTPUT);
  digitalWrite(15, LOW);
}

void loop() {
  digitalWrite(15, HIGH);
  delay(500);
  digitalWrite(15, LOW);
  delay(500);
}
