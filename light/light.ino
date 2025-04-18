//for help look at: https://github.com/Starmbi/hp_BH1750/wiki
#include <Arduino.h>
#include <hp_BH1750.h>  
#include <WiFi.h>
#include <HTTPClient.h>
//  include libraries
hp_BH1750 BH1750;       //  create the sensor

const char* ssid = "IIIIllllllIIIIllIII";
const char* password = "julmsaladus";
const char* serverURL = "http://192.168.150.176:5000/data";

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.println(WiFi.localIP());  // Optional: print IP

  bool avail = BH1750.begin(BH1750_TO_GROUND);// init the sensor with address pin connetcted to ground
                                              // result (bool) wil be be "false" if no sensor found
  if (!avail) {
    Serial.println("No BH1750 sensor found!");
    while (true) {};                                        
  }
}

void loop()
{ 
  
  //Light sensor data 
  BH1750.start();   //starts a measurement
  float lux=BH1750.getLux();  //  waits until a conversion finished
  Serial.println(lux);      
  

  // Wireless connection to Raspbi flask server
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    String json = "{\"Lux\":" + String(lux) + "}";
    int httpResponseCode = http.POST(json);

    Serial.print("Response: ");
    Serial.println(httpResponseCode);
    //Serial.println(http.errorToString(httpResponseCode));
    http.end();
  }

 delay(500);
}
