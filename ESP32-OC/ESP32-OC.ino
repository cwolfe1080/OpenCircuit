// OpenCircuit ESP32 Test Firmware

#define RX_PIN 12
#define TX_PIN 13

char buf[16];
uint8_t bi = 0;

void tx(const char *cmd) {
  Serial1.print(cmd);
  Serial1.print(';');
}

void rx() {
  while (Serial1.available()) {
    char c = Serial1.read();

    if (c == ';') {
      buf[bi] = '\0';
      Serial.print("RX: ");
      Serial.println(buf);
      if (!strcmp(buf, "TEST")) {
        Serial.println("Ping received.");
        tx("TEST_ACK");
      }
      else if (!strcmp(buf, "OFF")) {
        Serial.println("Power off requested");
        Serial1.print("OFF_ACK;"); 
        Serial1.flush();
        delay(20);              
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_27, LOW);
        esp_deep_sleep_start();
      }
      else {
        Serial.println("Unknown command.");
        tx("ERR");
      }
      bi = 0;
    }
    else if (bi < sizeof(buf) - 1) {
      buf[bi++] = c;
    }
  }
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("ESP32 Boot");
  Serial1.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  Serial.println("UART Ready");
}

void loop() {
  rx();
}