//INFORMACJE PODSTAWOWE
//Program: Serial - sterowanie dioda z komputera
//Autor:   Paweł Bartkiewicz 
//mail:    15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE 

//Dioda
//Dluzsze wyprowadzenie - zasilanie - pin 26
//Krotsze wyprowadzenie - masa - GND

const int LED = 26; 
String message = "";

void setup() {
  
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {
  
  if(Serial.available() > 0){
    message = Serial.readString();

    if(message.startsWith("start")){
      digitalWrite(LED, HIGH);

    } if(message.startsWith("mrugaj")){

      digitalWrite(LED, LOW); 
      delay(500);
      digitalWrite(LED, HIGH);
      delay(500);
      digitalWrite(LED, LOW); 
      delay(500);
      digitalWrite(LED, HIGH);
      delay(500);
      digitalWrite(LED, LOW); 
      delay(500);

    } if(message.startsWith("stop")){

      digitalWrite(LED, LOW); 
    }
  }
}
