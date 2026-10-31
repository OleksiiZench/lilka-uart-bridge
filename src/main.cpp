#include <Arduino.h>

constexpr int UART_RX_PIN = 47;  // P4
constexpr int UART_TX_PIN = 48;  // P3
constexpr uint32_t UART_BAUD = 1500000;

static uint8_t buf[1024];

void setup() {
  Serial.setTxBufferSize(16384);   // до begin()!
  Serial.setRxBufferSize(16384);   // до begin()!
  Serial.setTxTimeoutMs(100);      // чекати, а не викидати дані
  Serial.begin(115200);

  Serial1.setRxBufferSize(16384);
  Serial1.begin(UART_BAUD, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);
}

void loop() {
  size_t n = Serial1.available();
  if (n) {
    n = Serial1.readBytes(buf, min(n, sizeof(buf)));
    Serial.write(buf, n);
  }

  n = Serial.available();
  if (n) {
    n = Serial.readBytes(buf, min(n, sizeof(buf)));
    Serial1.write(buf, n);
  }
}
