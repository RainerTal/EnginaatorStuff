#include <BH1750.h>
#include <Wire.h>

// Create a BH1750 object
BH1750 lightMeter;

void setup() {
  Serial.begin(9600);

  // Initialize the I2C bus with explicit SDA and SCL pins
  Wire.begin(21, 22);  // SDA = GPIO21, SCL = GPIO22

  // Initialize the BH1750 sensor
  if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) { // You can use the detected address here
    Serial.println("Error initializing BH1750");
    while (1); // Halt execution if initialization fails
  }

  Serial.println(F("BH1750 Test begin"));
}

void loop() {
  // Read light level in lux
  float lux = lightMeter.readLightLevel();

  if (lux == -1) {
    Serial.println("Error reading light level");
  } else {
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");
  }

  delay(1000);  // Wait for 1 second
}
