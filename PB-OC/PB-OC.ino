#include <Adafruit_Arcada.h>
#include "palette.h"
#include "wiring_private.h"

Adafruit_Arcada arcada;

// Set up comms with ESP32
Uart FeatherUART(&sercom3,13,12,SERCOM_RX_PAD_1,UART_TX_PAD_0);
void SERCOM3_0_Handler() { FeatherUART.IrqHandler(); }
void SERCOM3_1_Handler() { FeatherUART.IrqHandler(); }
void SERCOM3_2_Handler() { FeatherUART.IrqHandler(); }
void SERCOM3_3_Handler() { FeatherUART.IrqHandler(); }

void drawPixel8(int16_t x, int16_t y, uint8_t color) {
  arcada.display->drawPixel(x, y, palette[color]);
}

void fillScreen8(uint8_t color) {
  arcada.display->fillScreen(palette[color]);
}

void wakeESP() {
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  delay(5);
  digitalWrite(10, HIGH);
  delay(200);
  digitalWrite(10, LOW);
  arcada.setBacklight(255);
}

void tx(const char *cmd) {
  FeatherUART.print(cmd);
  FeatherUART.print(';');
}

char buf[16];
uint8_t bi = 0;

void rx() {
  while (FeatherUART.available()) {
    char c = FeatherUART.read();
    if (c == ';') {
      buf[bi] = '\0';
      Serial.print("RX: ");
      Serial.println(buf);
      if (strcmp(buf, "OFF_ACK") == 0) {
        arcada.setBacklight(0);
      }
      bi = 0;
    } else if (bi < 15) {
      buf[bi++] = c;
      buf[bi] = '\0';
    }
  }
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
uint32_t holdStart = 0;
bool holding = false;
void setup() {
  arcada.arcadaBegin();
  arcada.displayBegin();
  arcada.setBacklight(255);  // 0-255
  Serial.begin(9600);
  pinPeripheral(12, PIO_SERCOM);
  pinPeripheral(13, PIO_SERCOM);
  FeatherUART.begin(9600);
  delay(1000);

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
 rx();
  if ((pressed_buttons & ARCADA_BUTTONMASK_START) &&
      (pressed_buttons & ARCADA_BUTTONMASK_SELECT)) {
    if (!holding) {
      holding = true;
      holdStart = millis();
    }
    if (millis() - holdStart > 2000) {
      wakeESP();
      holding = false;
    }
  } else {
    holding = false;
  }
 switch (l) {
  case 0: {
    if (!milc) {
      arcada.display->fillRect(2,60 + (oldMenuItem-1)*10,8,8,palette[0]);
      arcada.display->setCursor(2,60 + (menuItem-1)*10); arcada.display->print(">");
      milc=true;
    }
    if (pressed_buttons & ARCADA_BUTTONMASK_A) {
      if (menuItem == 7) {
        // Power Off
        tx("OFF");
        delay(500);
      }
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
    } else if ((pressed_buttons & ARCADA_BUTTONMASK_B)) {
      tx("TEST");
      delay(250);
    }
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