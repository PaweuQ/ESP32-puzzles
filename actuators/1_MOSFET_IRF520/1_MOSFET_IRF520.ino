//BASIC INFORMATION
// Program: controlling MOSFET IRF520 module with a button
// Author:  Paweł Bartkiewicz 
// email:   15g.pawel.bart@gmail.com
// Github:  PaweuQ

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


#define MOSFET 15   //control signal to transistor module
#define IP 14      //input pullup

bool CS = false;    //current button status
bool LS = false;    //last button status

bool current_MOSFET_status = false;
bool new_MOSFET_status = false;

void setup() 
{
  Serial.begin(9600);
  pinMode(MOSFET, OUTPUT);
  pinMode(IP, INPUT_PULLUP);
  digitalWrite(MOSFET, LOW);
}

void loop()
{
  CS = digitalRead(IP);

  if(LS != CS){
    if(CS == LOW){

      current_MOSFET_status = digitalRead(MOSFET);
      new_MOSFET_status = !current_MOSFET_status;
      digitalWrite(MOSFET, new_MOSFET_status);
      Serial.println("Change");
    }
  delay(50);
  }
  LS = CS;
}