//INFORMACJE PODSTAWOWE
//Program: Obsluga strzalek (4 przyciski)
//Autor: Paweł Bartkiewicz 
//mail: 15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE
// przy obecnym opoznieniu (50 ms) jedno nacisniecie
// to srednio 3 zarejestrowane klikniecia w programie

//POMYSL
// przyciski inkrementuja i dekrementuja wartosci zmiennych 
// w dwoch osiach X i Y

#define up    19
#define down  18
#define right 22
#define left  21

void setup() {
  
  Serial.begin(115200);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
}

void loop() {
  
  bool UP_button = digitalRead(up);
  bool DOWN_button = digitalRead(down);
  bool RIGHT_button = digitalRead(right);
  bool LEFT_button = digitalRead(left);

  if(UP_button == LOW){
    Serial.println("Gora");
    delay(50);
  }
  if(DOWN_button == LOW){
    Serial.println("Dol");
    delay(50);
  }
  if(RIGHT_button == LOW){
    Serial.println("Prawo");
    delay(50);
  }
  if(LEFT_button == LOW){
    Serial.println("Lewo");
    delay(50);
  }
}
