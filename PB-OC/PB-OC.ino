#include <Adafruit_Arcada.h>
#include "palette.h"

Adafruit_Arcada arcada;

void drawPixel8(int16_t x, int16_t y, uint8_t color) {
  arcada.display->drawPixel(x, y, palette[color]);
}

void fillScreen8(uint8_t color) {
  arcada.display->fillScreen(palette[color]);
}

void fillRect8(
  int16_t x,
  int16_t y,
  int16_t w,
  int16_t h,
  uint8_t color
) {
  arcada.display->fillRect(x, y, w, h, palette[color]);
}


void setup() {
  arcada.arcadaBegin();
  arcada.displayBegin();
  arcada.setBacklight(255);  // 0-255

  initPalette();
  fillScreen8(0);
  fillRect8(8, 10, 145, 30, 2);
  arcada.display->setCursor(17, 20);      // x, y position
  arcada.display->setTextColor(palette[0]); // Use one of your palette colors
  arcada.display->setTextSize(2);         // Scale factor (1 = 6x8 px)
  arcada.display->print("OpenCircuit");
  arcada.display->setCursor(50, 47);      // x, y position
  arcada.display->setTextColor(palette[2]); // Use one of your palette colors
  arcada.display->setTextSize(1);         // Scale factor (1 = 6x8 px)
  arcada.display->print("V0.0.1 BETA");
}

void loop() {
 // Start building menu select items next time. A should be start, B should be power off or something like that. You can add more options and eventually we'll incorporate WiFi stuff.
}