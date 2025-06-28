//INFORMACJE PODSTAWOWE
//Program: obsluga przycisku monostabilnego jako bistabilnego
//Autor: Paweł Bartkiewicz 
//mail: 15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE 

//Przycisk
//Schemat polaczen wewnatrz przycisku z 4 wyprowadzeniami
/*
      |      |
      |      |
      |--/ --|
      |      |
      |      |
*/
//Nacisniecie zamyka obwod i laczy wszystkie 4 wyprowadzenia

//Dioda
//Dluzsze wyprowadzenie - zasilanie - pin 18
//Krotsze wyprowadzenie - masa - GND

#define dioda 18
#define odczyt 15

bool CS = false; //current button status
bool LS = false; //last button status
bool cLEDs = false; //current LED status
bool nLEDs = false; //new button status

void setup() 
{
  Serial.begin(115200);
  pinMode(dioda, OUTPUT);
  pinMode(odczyt, INPUT_PULLUP);
  digitalWrite(dioda, LOW);
}

void loop()
{
  CS = digitalRead(odczyt);

  if(LS != CS){
    if(CS == LOW){

      cLEDs = digitalRead(dioda);
      nLEDs = !cLEDs;
      digitalWrite(dioda, nLEDs);
      Serial.println("Zmiana");
    }
  delay(50);
  }
  LS = CS;
}
