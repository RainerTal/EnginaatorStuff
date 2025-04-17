#include <Wire.h>

void setup() {
  Wire.begin(21, 22);  // SDA = GPIO21, SCL = GPIO22 for ESP32
  Serial.begin(9600);
  Serial.println("\nI2C Scanner");

  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found I2C device at address: 0x");
      Serial.println(address, HEX);
      delay(1000);
    }
  }
  Serial.println("Scanning done.");
}

void loop() {}
