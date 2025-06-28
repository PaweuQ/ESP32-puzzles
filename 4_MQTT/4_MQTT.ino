//INFORMACJE PODSTAWOWE
//Program: polaczenie MQTT
//Autor: Paweł Bartkiewicz 
//mail: 15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE 
///szkielet z polaczeniem WiFi i MQTT
///zawiera: 
///sprawdzenie lacznosci WiFi za pomoca diody (pin 23)
///funkcje odnawiajace polaczenie z wifi/serwerem mqtt po zerwaniu lacznosci 
///kazda otrzymana wiadomosc przez mqtt jest przypisywana do zmiennej rP, z ktorej mozna wygodnie korzystac w loop() poza funkcja
///poprzednia zawartosc rP kasuje sie po otrzymaniu nastepnej wiadomosci

///w petli glownej loop() jest przyklad wykorzystania mqtt do zaswiecenia diody i wyslania wiadomosci
///czyli akcja subscribe and publish

///biblioteke PubSubClient nalezy zainstalowac
///PubSubClient by Nick 0'Leary 

#include <WiFi.h>
#include <PubSubClient.h>
#define LED1 23 ///dioda sprawdzajaca polaczenie z wifi, wlacza sie po polaczeniu
#define LED2 18

///login i haslo do wifi
const char* ssid = "login";
const char* password = "password";

///publiczny serwer mqtt
///inne: 
///  broker.emqx.io
///  test.mosquitto.org
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;

///tworzenie instancji obiektu espClient klasy WiFiClient
///tworzenie instancji obiektu client klasy PubSubClient
///te nazwy po lewej to jakby klasy, a po prawej wystapienia tych klas
WiFiClient espClient;
PubSubClient client(espClient);

String rP; ///receivedPayload - otrzymana wiadomosc przez mqtt
bool flag1 = false;

void setup() 
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(115200);

  connectToWiFi();

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    if (client.connect("nazwa")) {
      Serial.println("Polaczono z serwerem MQTT");
      
      ///tu nalezy podac subskrybowany topic
      ///topic powinien byc taki sam jak w funkcji connectToMQTT
      client.subscribe("temat");
    } else {
      Serial.print("Nie udalo sie polaczyc, kod bledu:");
      Serial.print(client.state());
      Serial.println(" Ponowienie za 5 sekund...");
      delay(5000);
    }
  }
}

void loop() 
{
  ///sprawdzanie polaczenia z serwerem MQTT
  if (!client.connected()) 
  {
    connectToMQTT();
  }

  client.loop();
  checkWiFiConnection();

  ///przykladowe wykorzystanie zmiennej rP (received Payload) 
  ///po otrzymaniu wiadomosci "z" wlaczy sie dioda zielona
  ///zostanie tez wyslana wiadomosc "wlaczona" przez mqtt na topic "diode"
  ///po otrzymaniu wiadomosci "zz" dioda sie wylaczy

  if (rP == "z" && !flag1) 
  {  
    digitalWrite(LED1, HIGH);
    client.publish("temat", "wlaczona");
    flag1 = true; 
  }
  else if (rP == "zz" && flag1) 
  {
    digitalWrite(LED1, LOW);
    client.publish("temat", "wylaczona");
    flag1 = false;
  }
}

///funkcja odbierajaca wiadomosci MQTT
///zapisuje wiadomosc do zmiennej rP
void callback(char* topic, byte* payload, unsigned int length) 
{
  rP = ""; ///usuwanie poprzedniej zawartosci po kazdym wejscu do tej funkcji
  for (int i = 0; i < length; i++) 
  {
    rP += (char)payload[i];
  }
}

///laczenie z WiFi po uruchomieniu plytki
void connectToWiFi() 
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.println("Laczenie z WiFi...");
    delay(1000);
  }
  Serial.println("Polaczono z siecia WiFi!");
  digitalWrite(LED2, HIGH); 
}

///sprawdzanie polaczenia z WiFi
void checkWiFiConnection() 
{
  if (WiFi.status() != WL_CONNECTED) 
  {
    Serial.println("Polaczenie WiFi zostalo zerwane!");
    digitalWrite(LED2, LOW);
    connectToWiFi(); 
  }
}

///funkcja dzialajaca po zerwaniu lacznosci z serwerem mqtt
///probuje sie wtedy polaczyc ponownie 
///zadziala np. po zerwaniu polaczenia z wifi bo wtedy zerwie tez polaczenie z serwerem
void connectToMQTT() 
{
  while (!client.connected()) 
  {
    Serial.println("Laczenie z MQTT...");
    if (client.connect("nazwa")) 
    {
      Serial.println("Polaczono z serwerem MQTT!");
      client.subscribe("temat");
    } 
    else 
    {
      Serial.print("Blad polaczenia z MQTT, kod bledu: ");
      Serial.print(client.state());
      Serial.println(" Sprobuj ponownie za 5 sekund");
      delay(5000);
    }
  }
}
