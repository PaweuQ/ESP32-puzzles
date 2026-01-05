#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CS_PIN 5

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  Serial.begin(9600);
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 0); // jasność 0–15
  mx.clear();
  delay(5000);
}

void loop() {
  for (int col = 0; col < 32; col++) {
    for (int row = 0; row < 8; row++) {
      mx.setPoint(row, col, true);
      Serial.print("[");
      Serial.print(row);
      Serial.print("]");
      Serial.print("[");
      Serial.print(col);
      Serial.println("]");
      delay(500);
      if(row==7){
        for(int i = 7; i > -1; i--){
          mx.setPoint(i, col, false);
          delay(500);
        }
      }
      
      
    }
  }
}
