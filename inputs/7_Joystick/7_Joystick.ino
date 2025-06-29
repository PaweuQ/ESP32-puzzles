//INFORMACJE PODSTAWOWE
//Program: Obsluga joysticka
//Autor: Paweł Bartkiewicz 
//mail: 15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE
// zwraca wartosci 0-4095 w kazdej osi 
// w pozycji spoczynkowej zwraca okolo 1930

//Joystick 3.3 V
//wyprowadzenia VRX i VRY musza byc 
//podlaczone do pinow ADC (np. 32, 35)

#define VRX 32
#define VRY 35

void setup() {

  Serial.begin(115200);
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
}

void loop() {
  
  int x = analogRead(VRX);
  int y = analogRead(VRY);

  Serial.print("X: ");
  Serial.print(x);
  Serial.print("   Y: ");
  Serial.println(y);
  delay(1000);
}
