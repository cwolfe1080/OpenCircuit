void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("ESP32 online");
}

void loop() {
  Serial.println("Howdy!");
  delay(5000);
}