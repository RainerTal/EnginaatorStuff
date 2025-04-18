const int RELAY1_PIN = 25;  // GPIO21 connected to IN1
const int RELAY2_PIN = 26;  // GPIO22 connected to IN2

void setup() {
  Serial.begin(115200);
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  
  // Initialize relays to OFF state
  digitalWrite(RELAY1_PIN, HIGH);  // For LOW level trigger
  digitalWrite(RELAY2_PIN, HIGH);  // For LOW level trigger
  
  // If using HIGH level trigger, initialize with:
  // digitalWrite(RELAY1_PIN, LOW);
  // digitalWrite(RELAY2_PIN, LOW);
  
  Serial.println("Relay test program started");
}

void loop() {
  // Test Relay 1
  Serial.println("Relay 1 ON - Check multimeter for continuity");
  digitalWrite(RELAY1_PIN, LOW);  // For LOW level trigger (change to HIGH if using HIGH level trigger)
  delay(3000);  
  
  Serial.println("Relay 1 OFF - Check multimeter for no continuity");
  digitalWrite(RELAY1_PIN, HIGH); // For LOW level trigger (change to LOW if using HIGH level trigger)
  delay(3000);
  
  // Test Relay 2
  Serial.println("Relay 2 ON - Check multimeter for continuity");
  digitalWrite(RELAY2_PIN, LOW);  // For LOW level trigger
  delay(3000);
  
  Serial.println("Relay 2 OFF - Check multimeter for no continuity");
  digitalWrite(RELAY2_PIN, HIGH); // For LOW level trigger
  delay(3000);
}
