#ifndef own_mqtt_h
#define own_mqtt_h

extern int water_plant (char PumpNr, int water_time);

void mqtt_Setup();
void send_message(const char* topic, const char* payload);
void send_message(const char* topic, int payload);
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

//Because we can't include HumSens and MoistureShield
extern int moist_val[4];
extern int read_moist(int *val, char sensor);

WiFiClient espClient;
const char*     MQTT_BROKER_IP  = "192.168.169.100";
const char*     MQTT_SUB_TOPIC  = "water_ctrl"; 
int             MQTT_PORT       = 1883;
PubSubClient client(espClient);

//Setup mqtt
void mqtt_Setup() {
  client.setServer(MQTT_BROKER_IP, MQTT_PORT);  //Broker + Port setzen
  client.setCallback(callback);     //Fkt callback bei Nachrichtenempfang
}

//Reconnet to mqtt broker
void reconnect() {
    while (!client.connected()) {

      // Create a random client ID
      String clientId = "ESP8266_HumSens-";
      clientId += String(random(0xffff), HEX);
      Serial.print("Connecting");
      //Verbindungsversuch - keine Nachricht bei Erfolg
      if (!client.connect(clientId.c_str())) {
              delay(5000);
              Serial.print(".");
          }
      Serial.println();
      client.subscribe(MQTT_SUB_TOPIC);
      Serial.println("Connected and subscribed");
    }
    
}

//Send String
void send_message(const char* topic, const char* payload) {
  client.publish(topic, payload);
}

//Send int (converting int to string)
void send_message(const char* topic, int payload) {
  //Serial.print("Message sent");
  char buffer[33];
  itoa(payload, buffer, 10);
  const char* p = buffer;
  client.publish(topic, p);
}

//Aufruf bei Nachricht in Topic
void callback(char* topic, byte* payload, unsigned int length) {
    //erstelle msg-Array zur Verarbeitung
    char msg[length+1];
    for (int i = 0; i < length; i++) {
        msg[i] = (char)payload[i];
    }
    //End of line für fertigen String
    msg[length] = '\0';

    char *pump_str = strtok(msg, "/");
    char *watertime_str = strtok(NULL, "/");
     
    send_message("debug", "new command");
    unsigned int pump = atoi(pump_str);
    unsigned int water_time = atoi(watertime_str);
    send_message("debug/watering/pump", pump);
    send_message("debug/watering/time", water_time);
    if (water_time < 300)
        water_plant(pump-1, water_time*1000);
}

#endif own_mqtt_h
