#include <TFT_eSPI.h>
#include <SPI.h>
#include <SD.h>
#include <TJpg_Decoder.h>

// ===== TFT =====
TFT_eSPI tft = TFT_eSPI();

// ===== SD (VSPI) =====
#define SD_CS   5
#define SD_MOSI 23
#define SD_MISO 19
#define SD_SCLK 18

// ===== JPG callback =====
bool tft_output(int16_t x, int16_t y,
                uint16_t w, uint16_t h,
                uint16_t *bitmap)
{
    if (y >= tft.height() || x >= tft.width()) return false;

    tft.startWrite();
    tft.setAddrWindow(x, y, w, h);
    tft.pushColors(bitmap, w * h, true);
    tft.endWrite();

    return true;
}

void setup()
{
    Serial.begin(115200);
    delay(300);

    // TFT
    tft.init();
    tft.setRotation(2);
    tft.invertDisplay(false);
    tft.fillScreen(TFT_BLACK);
    Serial.println("TFT OK");

    // SD
    SPI.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);
    if (!SD.begin(SD_CS)) {
        Serial.println("SD FAIL");
        while (1);
    }
    Serial.println("SD OK");

    // JPG
    TJpgDec.setCallback(tft_output);
    TJpgDec.setSwapBytes(false);   // RGB565
    TJpgDec.setJpgScale(1);

    // rysuje pusty prostokat
    tft.drawRect(200, 200, 50, 50, TFT_BROWN);
    // rysuje okrag
    tft.drawCircle(225, 225, 25, TFT_PINK);
    // rysuje piksel
    tft.drawPixel(1,1,TFT_WHITE);
    tft.drawPixel(2,2,TFT_WHITE);
    tft.drawPixel(3,3,TFT_WHITE);
    tft.drawPixel(4,4,TFT_WHITE);
    tft.drawPixel(5,5,TFT_WHITE);
    tft.drawPixel(5,5,TFT_WHITE);
    tft.drawPixel(6,6,TFT_WHITE);
    // rysuje linie - wolna funkcja programowo
    tft.drawLine(8, 8, 20, 20, TFT_PURPLE);
    // rysuje linie pozioma - szybka funkcja, szybsze dzialanie
    tft.drawFastHLine(0, 40, 30, TFT_WHITE);
    // rysuje linie pionowa - szybka funkcja, szybsze dzialanie
    tft.drawFastVLine(50, 30, 120, TFT_GREEN);
    // rysuje wypelniony prostokat
    tft.fillRect(150, 400, 50, 50, TFT_BROWN);

}

void loop() {
/*
  tft.fillScreen(TFT_RED);
  tft.fillScreen(TFT_MAGENTA);
  TJpgDec.drawSdJpg(0, 0, "/test0.jpg");
*/

}
