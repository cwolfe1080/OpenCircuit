void setup() {
  Serial.begin(9600);

  Serial.println("test");

  // IMPORTANT: force UART to pins, not abstract Serial1 assumption
  Serial1.begin(115200, SERIAL_8N1);
}

void loop() {
  while (Serial1.available()) {
    Serial.write(Serial1.read());
  }
}