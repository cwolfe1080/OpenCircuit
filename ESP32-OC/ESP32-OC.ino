#define RX_PIN 7
#define TX_PIN 8

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ESP32 UART sender starting...");

  Serial1.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop() {
  Serial1.println("A");   // send A + newline
  Serial.println("Sent A");

  delay(500);
}