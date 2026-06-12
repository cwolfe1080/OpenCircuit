#include <Arduino.h>
#include "wiring_private.h"
#include <Adafruit_Arcada.h>

Adafruit_Arcada arcada;

// Custom UART on D13 (RX) and D12 (TX)
Uart FeatherUART(
  &sercom3,
  13,                      // RX pin
  12,                      // TX pin
  SERCOM_RX_PAD_1,
  UART_TX_PAD_0
);

// Interrupt handlers for SERCOM3
void SERCOM3_0_Handler() { FeatherUART.IrqHandler(); }
void SERCOM3_1_Handler() { FeatherUART.IrqHandler(); }
void SERCOM3_2_Handler() { FeatherUART.IrqHandler(); }
void SERCOM3_3_Handler() { FeatherUART.IrqHandler(); }

uint32_t rxCount = 0;

void setup() {
  Serial.begin(9600);
  delay(2000);

  Serial.println("PyBadge starting...");

  // Initialize the PyBadge display
  arcada.arcadaBegin();
  arcada.displayBegin();
  arcada.setBacklight(255);

  arcada.display->fillScreen(0x0000);
  arcada.display->setTextColor(0xFFFF);
  arcada.display->setTextSize(2);

  arcada.display->setCursor(15, 30);
  arcada.display->println("PYBADGE");

  arcada.display->setCursor(15, 55);
  arcada.display->println("RUNNING");

  arcada.display->setTextSize(1);
  arcada.display->setCursor(15, 100);
  arcada.display->println("Waiting for UART...");

  arcada.display->setCursor(15, 130);
  arcada.display->print("RX Count: 0");

  // Route D12/D13 to SERCOM hardware
  pinPeripheral(12, PIO_SERCOM);
  pinPeripheral(13, PIO_SERCOM);

  FeatherUART.begin(9600);

  Serial.println("PyBadge UART ready.");
}

void loop() {
  while (FeatherUART.available()) {
    char c = FeatherUART.read();

    // Print to USB serial monitor
    Serial.print("Received byte: ");
    Serial.print((int)c);
    Serial.print(" ('");
    if (c >= 32 && c <= 126) {
      Serial.print(c);
    } else {
      Serial.print('?');
    }
    Serial.println("')");

    // Update display counter
    rxCount++;
    arcada.display->fillRect(15, 130, 180, 12, 0x0000);
    arcada.display->setCursor(15, 130);
    arcada.display->print("RX Count: ");
    arcada.display->print(rxCount);

    // Echo the byte back to the ESP32
    FeatherUART.write(c);
  }
}