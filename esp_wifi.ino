#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN 9     // GPIO pin
#define DHTTYPE DHT11   // meie board

// WiFi credentials
const char* ssid = "IIIIllllllIIIIllIII";
const char* password = "julmsaladus";

// MQTT Broker IP address (Raspberry Pi's IP)
const char* mqtt_server = "192.168.150.176";  // Replace with Raspberry Pi IP

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Initialize WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

// Variables to store sensor readings
float humidity;
float temperatureC;
float temperatureF;
float heatIndexC;
float heatIndexF;

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  
  Serial.println(messageTemp);

  // Add any command processing logic here if the Raspberry Pi sends commands
  // For example, if the Raspberry Pi sends "getReading" on "esp32/commands" topic
  if (String(topic) == "esp32/commands") {
    if (messageTemp == "getReading") {
      readDHTSensor();
      publishSensorData();
    }
  }
}

void reconnect() {
  // Loop until we're reconnected to the MQTT broker
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      
      // Subscribe to command topic
      client.subscribe("esp32/commands");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void readDHTSensor() {
  // Read humidity
  humidity = dht.readHumidity();
  // Read temperature in Celsius (default)
  temperatureC = dht.readTemperature();
  // Read temperature in Fahrenheit
  temperatureF = dht.readTemperature(true);

  // Check if any reads failed
  if (isnan(humidity) || isnan(temperatureC) || isnan(temperatureF)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index
  heatIndexC = dht.computeHeatIndex(temperatureC, humidity, false);
  heatIndexF = dht.computeHeatIndex(temperatureF, humidity);

  // Output to Serial for debugging
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperatureC);
  Serial.print(F("°C "));
  Serial.print(temperatureF);
  Serial.print(F("°F  Heat index: "));
  Serial.print(heatIndexC);
  Serial.print(F("°C "));
  Serial.print(heatIndexF);
  Serial.println(F("°F"));
}

void publishSensorData() {
  // Publish humidity
  char humString[8];
  dtostrf(humidity, 1, 2, humString);
  client.publish("esp32/humidity", humString);

  // Publish temperature in Celsius
  char tempCString[8];
  dtostrf(temperatureC, 1, 2, tempCString);
  client.publish("esp32/temperatureC", tempCString);

  // Publish temperature in Fahrenheit
  char tempFString[8];
  dtostrf(temperatureF, 1, 2, tempFString);
  client.publish("esp32/temperatureF", tempFString);

  // Publish heat index in Celsius
  char hicString[8];
  dtostrf(heatIndexC, 1, 2, hicString);
  client.publish("esp32/heatIndexC", hicString);

  // Publish heat index in Fahrenheit
  char hifString[8];
  dtostrf(heatIndexF, 1, 2, hifString);
  client.publish("esp32/heatIndexF", hifString);
}

void setup() {
  Serial.begin(9600);
  
  // Initialize DHT sensor
  dht.begin();
  
  // Setup WiFi connection
  setup_wifi();
  
  // Configure MQTT server and callback
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  Serial.println(F("DHT22 with MQTT initialized!"));
}

void loop() {
  // Ensure MQTT connection is maintained
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read sensor data every 30 seconds and publish
  static unsigned long lastSensorReadTime = 0;
  if (millis() - lastSensorReadTime > 30000) {
    lastSensorReadTime = millis();
    readDHTSensor();
    publishSensorData();
  }
}
