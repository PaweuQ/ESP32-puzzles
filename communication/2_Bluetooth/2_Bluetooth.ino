//INFORMACJE PODSTAWOWE
//Program: Połączenie bluetooth
//Autor:   Paweł Bartkiewicz 
//mail:    15g.pawel.bart@gmail.com

//INFORMACJE DODATKOWE 
//biblioteka nie wymaga instalacji
//esp32 jest widoczne pod taka nazwa, jaka wpiszesz w BT.begin (20 linia)

//ten program moze sie laczyc tylko z jednym telefonem o nazwie Live 9S
//aby byl bardziej funkcjonalny, musi byc mozliwa podmiana klienta Bluetooth z zewnatrz
//bez koniecznosci zmieniania kodu

#include <BluetoothSerial.h>

bool flag1 = false; 
String MessageConverted = "";
char MessageBluetooth = 'N';
BluetoothSerial BT; 

void setup() 
{
  Serial.begin(115200);
  BT.begin("Live 9S");
}

void loop() 
{
  if(BT.hasClient() == true && flag1 == false){
    BT.print("Wiadomosc testowa\n");
    Serial.println("Polaczono z Bluetooth");
    flag1 = true;
    delay(2000);
  } 

  if(BT.hasClient() == false){ reconnect(); }
  
  if (BT.available()){

    // czyszczenie poprzedniej wiadomosci i znaku
    MessageConverted = "";
    char MessageBluetooth = 'N';

    // odczyt danych do momentu napotkania znaku nowej linii ('\n')
    while (BT.available()) {
      MessageBluetooth = BT.read();
      if (MessageBluetooth == '\n') {
        break;  // konczy petle while po otrzymaniu ('\n')
      }
      MessageConverted += MessageBluetooth;
    }
    // wyswietlanie wiadomosci na serialu
    if (MessageConverted.length() > 0) {
      Serial.println("Received message: " + MessageConverted);
    }
  }
}

void reconnect(){
  if(!BT.connected()){
    BT.begin("Live 9S");
    Serial.println("Laczenie Bluetooth");
    flag1 = false;
    delay(2000);
  }
}