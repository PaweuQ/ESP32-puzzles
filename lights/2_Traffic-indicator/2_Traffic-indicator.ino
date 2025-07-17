//INFORMACJE PODSTAWOWE
//Program: Sygnalizator swietlny
//Autor: Paweł Bartkiewicz 
//mail: 15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE
//sekwencja zaczyna sie od zielonego swiatla

//czas trwania kazdego ze swiatel mozna latwo dostosowac
//zmieniajac opoznienia

const int zielona  = 21;
const int zolta    = 19;
const int czerwona = 18;

void setup() {
  pinMode(zielona, OUTPUT);
  pinMode(zolta, OUTPUT);
  pinMode(czerwona, OUTPUT);
}

void loop() {
  lights();
}

void lights(){
  digitalWrite(zielona, HIGH);
  delay(5000);
  digitalWrite(zielona, LOW);
  digitalWrite(zolta, HIGH);
  delay(2000);
  digitalWrite(zolta, LOW);
  digitalWrite(czerwona, HIGH);
  delay(5000);
  digitalWrite(zolta, HIGH);
  delay(2000);
  digitalWrite(czerwona, LOW);
  digitalWrite(zolta, LOW);
}
