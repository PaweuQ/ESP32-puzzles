//BASIC INFORMATION
// Program: 2.8" TFT 320x240 display
// Author:  Paweł Bartkiewicz 
// email:   15g.pawel.bart@gmail.com

#include <Adafruit_GFX.h>    // Core graphics library by Adafruit
#include <Arduino_ST7789.h> // Hardware-specific library for ST7789 (with or without CS pin)
#include <SPI.h>

#define TFT_MISO -1
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   27  // Chip select control pin
#define TFT_DC   32  // Data Command control pin
#define TFT_RST   15  // Reset pin (could connect to RST pin)

Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_CS); //for display with CS pin

void setup(void)
{
    Serial.begin(9600);
    tft.init(240, 320);   // initialize a ST7789 chip, 240x320 pixels
    tft.setRotation(0);

    tft.fillScreen(BLACK);
}

void loop()
{
    // Pixel drawing
    tft.drawPixel(120, 160, WHITE);  // 1 white pixel on the middle of screen
    delay(1000);

    // Line drawing
    tft.drawLine(10, 10, 230, 10, RED);  // horizontal red line 
    tft.drawLine(10, 10, 10, 310, GREEN); // vertical green line
    delay(1000);

    // Rectangle drawing
    tft.drawRect(50, 50, 100, 60, YELLOW); // Empty rectangle
    delay(1000);

    // Filled rectangle drawing
    tft.fillRect(80, 100, 60, 60, CYAN);
    delay(1000);

    // Circle drawing
    tft.drawCircle(120, 200, 30, BLUE);
    tft.fillCircle(180, 200, 20, MAGENTA); // Filled rectangle
    delay(1000);

    // Text displaying
    tft.setCursor(50, 250);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Hello world!");

    delay(2000);
    
    // Fill the screen to start the test from beginning
    tft.fillScreen(BLACK);
}

