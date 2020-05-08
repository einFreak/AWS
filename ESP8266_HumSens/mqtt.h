#ifndef own_mqtt_h
#define own_mqtt_h


void mqtt_Setup();
void send_message(const char* topic, const char* payload);
void send_message(const char* topic, int payload);
void callback(char* topic, byte* payload, unsigned int length);

//Because we can't include HumSens and MoistureShield
extern int moist_val[4];
extern int read_moist(int *val, int sensor);

WiFiClient espClient;
const char*     MQTT_BROKER_IP  = "192.168.178.190";
const char*     MQTT_SUB_TOPIC  = "/controll"; //zB "/home/data" - momentan unnötig
int             MQTT_PORT       = 1883;
PubSubClient client(espClient);

//Setup mqtt
void mqtt_Setup() {
  client.setServer(MQTT_BROKER_IP, MQTT_PORT);  //Broker + Port setzen
  client.setCallback(callback);     //Fkt callback bei Nachrichtenempfang
}


//Send String
void send_message(const char* topic, const char* payload) {
  client.publish(topic, payload);
}

//Send int (converting int to string)
void send_message(const char* topic, int payload) {
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
    //Serial.println();

    //End of line für fertigen String
    msg[length] = '\0'; 

    read_moist(moist_val, msg[0]);

}

#endif own_mqtt_h
