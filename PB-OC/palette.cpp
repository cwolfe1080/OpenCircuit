#include "palette.h"

uint16_t palette[256];

inline uint16_t rgb(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) |
         ((g & 0xFC) << 3) |
         (b >> 3);
}

void initPalette() {
  // Default everything to black.
  for (int i = 0; i < 256; i++) {
    palette[i] = 0x0000;
  }

  // Basic colors.
  palette[0] = 0x0000; // Black
  palette[1] = 0xFFFF; // White
  palette[2] = rgb(0, 151, 156); // Arduino Teal
  palette[3] = 0x07E0; // Green
  palette[4] = 0x001F; // Blue
  palette[5] = 0xFFE0; // Yellow
  palette[6] = 0x5A; // Turqoise
  palette[6] = 0xF800;  // Red
}