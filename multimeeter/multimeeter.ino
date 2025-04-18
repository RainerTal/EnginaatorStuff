 // GPIO21 connected to IN1const int RELAY2_PIN = 26;  // GPIO22 connected to IN2

void setup() {
  Serial.begin(115200);
  pinMode(RELAY2_PIN, OUTPUT);
  
  // Initialize relays to OFF state
  digitalWrite(RELAY2_PIN, HIGH);  // For LOW level trigger
  
  // If using HIGH level trigger, initialize with:
  // digitalWrite(RELAY1_PIN, LOW);
  // digitalWrite(RELAY2_PIN, LOW);
  
  Serial.println("Relay test program started");
}

void loop() {
  // Test Relay 1
  
  // Test Relay 2
  Serial.println("Relay 2 ON - Check multimeter for continuity");
  digitalWrite(RELAY2_PIN, LOW);  // For LOW level trigger
  delay(3000);
  
  Serial.println("Relay 2 OFF - Check multimeter for no continuity");
  digitalWrite(RELAY2_PIN, HIGH); // For LOW level trigger
  delay(3000);
}
