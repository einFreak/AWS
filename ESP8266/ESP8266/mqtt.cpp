#include "mqtt.h"
#include "Arduino.h"

//Because we can't include MoistureShield
extern int water_plant (char PumpNr, int water_time);

WiFiClient espClient;
PubSubClient MQTTclient(espClient);

const char*     MQTT_BROKER_IP  = "192.168.169.100";
const char*     MQTT_SUB_TOPIC  = "water_ctrl"; 
int             MQTT_PORT       = 1883;

//Setup mqtt
void mqtt_Setup() {
  MQTTclient.setServer(MQTT_BROKER_IP, MQTT_PORT);  //Broker + Port setzen
  MQTTclient.setCallback(callback);     //Fkt callback bei Nachrichtenempfang
}

//Reconnet to mqtt broker
void MQTTreconnect() {
    while (!MQTTclient.connected()) {

    // Create a random client ID
    String clientId = "ESP8266_HumSens-";
    clientId += String(random(0xffff), HEX);
    
    //Verbindungsversuch - keine Nachricht bei Erfolg
    if (!MQTTclient.connect(clientId.c_str())) {
            delay(5000);
        }
    }
    MQTTclient.subscribe(MQTT_SUB_TOPIC);
}

//Send String
void send_message(const char* topic, const char* payload) {
  MQTTclient.publish(topic, payload);
}

//Send int (converting int to string)
void send_message(const char* topic, int payload) {
  char buffer[33];
  itoa(payload, buffer, 10);
  const char* p = buffer;
  MQTTclient.publish(topic, p);
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
    if (water_time < 60)
        water_plant(pump, water_time*1000);

}
