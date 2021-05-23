#ifndef own_mqtt_h
#define own_mqtt_h

#include "PubSubClient.h"
#include "ESP8266WiFi.h"

extern WiFiClient espClient;
extern PubSubClient MQTTclient;

extern const char*     MQTT_BROKER_IP;
extern const char*     MQTT_SUB_TOPIC; 
extern int             MQTT_PORT;

void mqtt_Setup();
void MQTTreconnect();
void send_message(const char* topic, const char* payload);
void send_message(const char* topic, int payload);
void callback(char* topic, byte* payload, unsigned int length);

#endif
