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

    tft.fillScreen(TFT_BLACK);
    TJpgDec.drawSdJpg(0, 0, "/test1.jpg");
}

void loop() {}
