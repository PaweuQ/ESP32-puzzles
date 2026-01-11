#include <TFT_eSPI.h>

TFT_eSPI tft;

// =====================================================
// Pomocnicza pauza między testami
// =====================================================
void wait(uint16_t ms = 1500) {
  delay(ms);
}

// =====================================================
// Test pikseli
// =====================================================
void testPixels() {
  tft.fillScreen(TFT_BLACK);

  for (int i = 0; i < 2000; i++) {
    int x = random(tft.width());
    int y = random(tft.height());
    uint16_t color = random(0xFFFF);
    tft.drawPixel(x, y, color);
  }

  wait();
}

// =====================================================
// Test linii
// =====================================================
void testLines() {
  tft.fillScreen(TFT_BLACK);

  for (int i = 0; i < tft.width(); i += 10) {
    tft.drawLine(0, 0, i, tft.height(), TFT_RED);
    tft.drawLine(tft.width(), 0, i, tft.height(), TFT_GREEN);
  }

  wait();
}

// =====================================================
// Prostokąty
// =====================================================
void testRectangles() {
  tft.fillScreen(TFT_BLACK);

  for (int i = 0; i < 10; i++) {
    int margin = i * 10;
    tft.drawRect(
      margin,
      margin,
      tft.width() - margin * 2,
      tft.height() - margin * 2,
      TFT_WHITE
    );
  }

  wait();

  tft.fillScreen(TFT_BLACK);
  for (int i = 0; i < 6; i++) {
    tft.fillRect(
      20 + i * 40,
      40 + i * 30,
      60,
      40,
      random(0xFFFF)
    );
  }

  wait();
}

// =====================================================
// Okręgi
// =====================================================
void testCircles() {
  tft.fillScreen(TFT_BLACK);

  int cx = tft.width() / 2;
  int cy = tft.height() / 2;

  for (int r = 20; r < 150; r += 20) {
    tft.drawCircle(cx, cy, r, TFT_YELLOW);
  }

  wait();

  tft.fillScreen(TFT_BLACK);
  for (int i = 0; i < 6; i++) {
    tft.fillCircle(
      random(tft.width()),
      random(tft.height()),
      random(10, 40),
      random(0xFFFF)
    );
  }

  wait();
}

// =====================================================
// Trójkąty
// =====================================================
void testTriangles() {
  tft.fillScreen(TFT_BLACK);

  for (int i = 0; i < 6; i++) {
    tft.drawTriangle(
      random(tft.width()), random(tft.height()),
      random(tft.width()), random(tft.height()),
      random(tft.width()), random(tft.height()),
      random(0xFFFF)
    );
  }

  wait();
}

// =====================================================
// Tekst – podstawowe czcionki Adafruit GFX
// =====================================================
void testTextBasic() {
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(1);
  tft.setCursor(10, 10);
  tft.println("Text size 1");

  tft.setTextSize(2);
  tft.println("Text size 2");

  tft.setTextSize(3);
  tft.println("Text size 3");

  wait();
}

// =====================================================
// Czcionki TFT_eSPI (wbudowane)
// =====================================================
void testFonts() {
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_CYAN, TFT_BLACK);

  tft.loadFont("NotoSansBold15"); // jeśli masz wgrane do SPIFFS
  tft.drawString("Custom font", 10, 20);
  tft.unloadFont();

  tft.setTextFont(2);
  tft.drawString("Font 2", 10, 60);

  tft.setTextFont(4);
  tft.drawString("Font 4", 10, 100);

  wait();
}

// =====================================================
// Test szybkości wypełniania ekranu
// =====================================================
void testFillSpeed() {
  uint32_t start;

  start = millis();
  tft.fillScreen(TFT_RED);
  tft.fillScreen(TFT_GREEN);
  tft.fillScreen(TFT_BLUE);
  uint32_t elapsed = millis() - start;

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  tft.printf("Fill time: %lu ms", elapsed);

  wait(3000);
}

// =====================================================
// SETUP
// =====================================================
void setup() {
  Serial.begin(9600);
  delay(500);

  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(false);
  tft.fillScreen(TFT_BLACK);

  Serial.println("TFT test start");
}

// =====================================================
// LOOP – sekwencja testów
// =====================================================
void loop() {
  testPixels();
  testLines();
  testRectangles();
  testCircles();
  testTriangles();
  testTextBasic();
  testFillSpeed();
}
