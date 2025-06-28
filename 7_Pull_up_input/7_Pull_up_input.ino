//BASIC INFORMATION
// Program: pull-up input support with test 
// Author:  Paweł Bartkiewicz 
// email:   15g.pawel.bart@gmail.com
//
//ADDITIONAL INFORMATION 
//
//FOR LED 
// longer LED pin  - pin 15 (power supply)
// shorter LED pin - GND
//
//FOR TEST
// as part of the test, connect one end of the wire to GND 
// touch pin 15 with the other end -> LED should light up

#define LED 18
#define IP  15 //input pull-up pin
int S = 0; //variable holding the state of input_pullup

void setup() {
  pinMode(IP, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {

  //continuous input checking 
  S = digitalRead(IP);

  //closing the circuit GND-15 will light up the LED
  if (S == LOW){
    digitalWrite(LED, HIGH);
  }

  //opening the circuit GND-15 will turn off the LED
  if (S == HIGH){
    digitalWrite(LED, LOW);
  }
}
