//INFORMACJE PODSTAWOWE
//Program: polaczenie z WiFi
//Autor: Paweł Bartkiewicz 
//mail: 15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE 
//brak

#include <WiFi.h>

const char* ssid = "login";
const char* password = "password";

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED);{
    Serial.println("Laczenie z Wifi...");
    delay(1000);
  }
  Serial.println("Polaczono z siecia WiFi!");
}

void loop() 
{

}
