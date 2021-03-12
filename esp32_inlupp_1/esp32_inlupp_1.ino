#include <WiFi.h>
#include "AzureIotHub.h"
#include "Esp32MQTTClient.h"
#include <DHT.h>
#include <ArduinoJson.h>

#define INTERVAL 1000 * 5
#define DHT_PIN 21
#define DHT_TYPE DHT11

char *ssid = "Slivo";
char *pass = "David123";
char *conn = "HostName=example26february-IotHub.azure-devices.net;DeviceId=B8:F0:09:93:C5:5C;SharedAccessKey=Xe9cPPIdDFqA50FjXyo+A2OaQnFn6kof41RKnBeWrKU=";
bool messagePending = false;
time_t epochTime;

unsigned long prevMillis = 0;
float prevTemperature = 0;

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  initSerial();
  initDHT();
  initWifi();
  initDevice();
  initTime();

  delay(2000);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  unsigned long currentMillis = millis();
  epochTime = time(NULL);

  if(!messagePending) {
    if((currentMillis - prevMillis) >= INTERVAL) {
      prevMillis = currentMillis;
  
      if(!(std::isnan(temperature)) && !(std::isnan(humidity))) {
        
        if((temperature + 1) > prevTemperature || (temperature - 1) < prevTemperature) {
          prevTemperature = temperature;
  
          char payload[256];
          DynamicJsonDocument doc(1024);
          doc["temperature"] = temperature;
          doc["humidity"]   = humidity;
          doc["unixTime"] = epochTime;
          serializeJson(doc, payload); 
          
          SendMessage(payload);
        } 
      }   
    }  
  }

  Esp32MQTTClient_Check();
  delay(100);
}
