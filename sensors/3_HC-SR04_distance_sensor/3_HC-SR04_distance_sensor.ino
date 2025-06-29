//INFORMACJE PODSTAWOWE
//Program: Pomiar odleglosci czujnikiem HC-SR04
//Autor: Paweł Bartkiewicz 
//mail: 15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE
//zasilanie 5 V
//ponizej 4 cm pojawiaja sie bledy pomiaru
//czujnik moze byc wykorzystany do wykrywania obiektow 

const int trigPin = 19; 
const int echoPin = 21;

const float SoundSpeed = 0.0343;

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH);
  float distance = duration * SoundSpeed / 2;

  delay(1000);

  Serial.print("Odleglosc: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance<5){
    Serial.println("Odleglosc mniejsza niz 5 cm");
  }

  if (distance>20){
    Serial.println("Odleglosc wieksza niz 20 cm");
  }
}
