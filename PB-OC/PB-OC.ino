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

int l=0;
int menuItem=1;
bool milc=false;
int oldMenuItem=1;
uint32_t t0 = 0;   // last battery update time
float bat = 0;
void setup() {
  arcada.arcadaBegin();
  arcada.displayBegin();
  arcada.setBacklight(255);  // 0-255
  Serial.begin(9600);
  while (!Serial) {
    delay(10);
  }

  initPalette();
  fillScreen8(0);
  fillRect8(8, 10, 145, 30, 2);
  arcada.display->setCursor(17, 20);      // x, y position
  arcada.display->setTextColor(palette[0]); // Use one of your palette colors
  arcada.display->setTextSize(2);         // Scale factor (1 = 6x8 px)
  arcada.display->print("OpenCircuit");
  arcada.display->setCursor(10, 44);      // x, y position
  arcada.display->setTextColor(palette[2]); // Use one of your palette colors
  arcada.display->setTextSize(1); arcada.display->print("V1 BETA");
  arcada.display->setCursor(10, 60); arcada.display->print("Grand Prix");
  arcada.display->setCursor(10, 70); arcada.display->print("Custom Race");
  arcada.display->setCursor(10, 80); arcada.display->print("Time Trial");
  arcada.display->setCursor(10, 90); arcada.display->print("Competitive (coming soon)");
  arcada.display->setCursor(10, 100); arcada.display->print("Manage tracks");
  arcada.display->setCursor(10, 110); arcada.display->print("Settings");
  arcada.display->setCursor(10, 120); arcada.display->print("Power off");

}

void loop() {
 uint8_t pressed_buttons = arcada.readButtons();
 uint32_t t = millis();

 switch (l) {
  case 0: {
    if (!milc) {
      arcada.display->fillRect(2,60 + (oldMenuItem-1)*10,8,8,palette[0]);
      arcada.display->setCursor(2,60 + (menuItem-1)*10); arcada.display->print(">");
      milc=true;
    }
    if (pressed_buttons & ARCADA_BUTTONMASK_A) {
      // Continue here
    } else if ((pressed_buttons & ARCADA_BUTTONMASK_DOWN) && (menuItem < 7)) {
      oldMenuItem=menuItem;
      menuItem++;
      milc=false;
      delay(220);
    } else if ((pressed_buttons & ARCADA_BUTTONMASK_UP) && (menuItem > 1)) {
      oldMenuItem=menuItem;
      menuItem--;
      milc=false;
      delay(220);

    }

    if (t - t0 > 1000) {
      t0 = t;
      bat = arcada.readBatterySensor();
      arcada.display->fillRect(100, 44, 80, 8, palette[0]);
      arcada.display->setCursor(100, 44);
      arcada.display->print("BAT: ");
      arcada.display->print(bat);
    }
    break;
  }
 }
}