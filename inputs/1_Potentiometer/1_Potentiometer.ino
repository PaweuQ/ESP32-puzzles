//INFORMACJE PODSTAWOWE
//Program: obsluga potencjometru - regulowanie jasnosci diody LED
//Autor:   Paweł Bartkiewicz 
//mail:    15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE 

//Potencjometr
//srodkowe wyprowadzenie do ADC, np. pin 34 w ESP32
//prawe    wyprowazdenie do zasilania 3.3/5 V
//lewe     wyprowadzenie do GND

// inny sposob definiowania pinu zamiast #define
const int LED = 26; //LED             
const int POT = 34; //potencjometr

int POTv = 0; //odczyt z potencjometra

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(POT, INPUT);
}

void loop() {
  POTv = analogRead(POT);

  //potencjometr 10K przy 3.3 V daje wartosci 0-4096 
  //Jasnosc zielonej diody zmienia sie plynnie miedzy wartosciami ~~0-250
  //wiec przeskalowalem wartosci z potencjometra, dzielac przez 16

  Serial.print("Wartosc odczytu: %d"); Serial.println(POTv/16);
  analogWrite(LED, POTv/16);
  delay(200);
}


