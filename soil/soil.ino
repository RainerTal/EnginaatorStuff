#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "IIIIllllllIIIIllIII";
const char* password = "julmsaladus";
const char* serverURL = "http://192.168.150.176:5000/data";


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.println(WiFi.localIP());  // Optional: print IP
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(500);        // delay in between reads for stability

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    String json = "{\"Soil\":" + String(sensorValue) + "}";
    int httpResponseCode = http.POST(json);

    Serial.print("Response: ");
    Serial.println(httpResponseCode);
    //Serial.println(http.errorToString(httpResponseCode));
    http.end();
  }
}
