// ESP32 Feather V2
// TX: GPIO13  -> PyBadge D13
// RX: GPIO12  <- PyBadge D12

#define RX_PIN 12
#define TX_PIN 13

void setup() {
  Serial.begin(9600);
  delay(2000);

  Serial.println("ESP32 starting...");

  Serial1.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  Serial.println("ESP32 UART ready.");
}

void loop() {
  // Send one byte
  Serial1.write('A');
  Serial.println("Sent: A");

  // Print anything we get back
  while (Serial1.available()) {
    char c = Serial1.read();

    Serial.print("Received byte: ");
    Serial.print((int)c);
    Serial.print(" ('");
    if (c >= 32 && c <= 126) {
      Serial.print(c);
    } else {
      Serial.print('?');
    }
    Serial.println("')");
  }

  delay(500);
}