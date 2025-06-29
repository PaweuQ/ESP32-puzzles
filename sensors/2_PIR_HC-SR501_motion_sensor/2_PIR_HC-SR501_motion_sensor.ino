//INFORMACJE PODSTAWOWE
//Program: Obsluga czujnika ruchu PIR HC-SR501
//Autor: Paweł Bartkiewicz 
//mail: 15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE

//OPIS 
//PIR - passive ultra red 
//czujnik PIR HC-SR501 reaguje na zmiany temperatury powietrza
//wykrywajac w ten sposob ruch istot zywych
//kat widzenia 100 stopni, zakres dzialania 7 metrow

//PODLACZENIE
//odwroc czujnik do gory nogami i ustaw pinami do siebie
//od lewej: VCC, OUT, GND

//REGULACJA 
//odwroc do gory nogami i ustaw pokretlami do siebie
//po lewej:  pokretlo do zmiany czulosci - odleglosc wykrywania
//po prawej: pokretlo do zmiany czasu dzialania - czas stanu wysokiego po wykryciu

//ZWORKA
//wolny pin na zewnatrz = ponowne wyzwalanie dopkoki wykrywany jest ruch
//wolny pin do wewnatrz = jedno wyzwolenie i brak reakcji na dalszy ruch

//PROGRAMOWANIE
//digitalRead(PIR) zwraca HIGH po wykryciu ruchu i LOW domyslnie

const int PIR = 23;



void setup() {

  pinMode(PIR, INPUT);
  Serial.begin(115200);
}

void loop() {

  if(digitalRead(PIR)){
    Serial.println("Wykryto ruch!");
  } else {
    Serial.println("Brak ruchu.");
  }
  delay(500);
}
