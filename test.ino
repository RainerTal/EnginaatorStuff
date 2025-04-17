#include <Wire.h>
#include <BH1750.h>

// Define the I2C pins for ESP32
#define SDA_PIN 21
#define SCL_PIN 22

BH1750 lightMeter;

void setup() {
  Serial.begin(115200);
  
  // Initialize the I2C bus with the defined pins
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // Initialize the sensor
  lightMeter.begin();
  
  Serial.println(F("BH1750 Light Sensor Test"));
}

void loop() {
  // Read light level
  float lux = lightMeter.readLightLevel();
  
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  
  delay(1000);  // Wait for 1 second before next reading
}