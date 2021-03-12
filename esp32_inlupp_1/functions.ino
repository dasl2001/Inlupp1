void initSerial() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Serial initialized.");
}

void initDHT() {
  dht.begin();
  Serial.println("DHT initialized.");
}

void initWifi() {
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.println("WiFi initialized.");
}

void initDevice() {
  Esp32MQTTClient_Init((uint8_t *) conn, true);
  Esp32MQTTClient_SetSendConfirmationCallback(sendCallback);
}

void initTime() {
  configTime(3600, 0, "pool.ntp.org", "time.nist.gov");

  while(true) {
    epochTime = time(NULL);

    if(epochTime <= 30000) { delay(1000); }
    else { Serial.printf("NTP EpochTime is: %lu. \r\n", epochTime); break; }  
  }
}

void sendCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result) {
  if(result == IOTHUB_CLIENT_CONFIRMATION_OK) {
    Serial.println("Message confimred");
    messagePending = false;
  }
}

void SendMessage(char *payload) {
  messagePending = true;
  
  EVENT_INSTANCE *message = Esp32MQTTClient_Event_Generate(payload, MESSAGE);
  Esp32MQTTClient_Event_AddProp(message, "School", "Nackademin");
  Esp32MQTTClient_Event_AddProp(message, "Name", "David Slivo");
  
  Esp32MQTTClient_SendEventInstance(message);
}
