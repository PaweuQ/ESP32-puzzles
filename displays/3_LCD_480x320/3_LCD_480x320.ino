#include <TFT_eSPI.h>

TFT_eSPI tft;

void setup() {

  Serial.begin(9600);
  delay(500);

  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(false);
}

void loop() {

  tft.fillScreen(TFT_RED);
  delay(1000);

  tft.fillScreen(TFT_GREEN);
  delay(1000);

  tft.fillScreen(TFT_BLUE);
  delay(1000);
}
