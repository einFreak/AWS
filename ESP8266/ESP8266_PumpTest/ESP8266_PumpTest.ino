#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "NetworkInfo.h"
#include "mqtt.h"
#include "MoistureShield.h"
#include "AutoWatering.h"

/*
 * moved to NetworkInfo.h
 * const char*   SSID            = "NETZWERKNAME";
 * const char*   PASSWORD        = "NETZWERKSCHLÜSSEL"; 
 */
int moist_val[4] = {0, 0 ,0 ,0};
void setup();
void loop();
void setup_wifi();
void reconnect();
 
//Board starting setup
void setup() {
    ShieldSetup();
    setup_wifi();
    mqtt_Setup();
}

/*  
 *  loop running constantly on board, 
 *  call client.loop regulary to check for incomming messages
 */
void loop() {

    //Check WiFi
    if (WiFi.status() != WL_CONNECTED) {
        setup_wifi();
    }
    
    //check mqtt status
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    //reading values
    delay(5000);
    water_plant(0);
    water_plant(1);
    water_plant(2);
    water_plant(3);
    water_plant(4);
    water_plant(5);
    
    
}

//Connecting WIFI
void setup_wifi() {
    delay(10);
 
    WiFi.begin(SSID, PASSWORD);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}

//Reconnet to mqtt broker
void reconnect() {
    while (!client.connected()) {

    // Create a random client ID
    String clientId = "ESP8266_HumSens-";
    clientId += String(random(0xffff), HEX);
    
    //Verbindungsversuch - keine Nachricht bei Erfolg
    if (!client.connect(clientId.c_str())) {
            delay(5000);
        }
    }
    client.subscribe(MQTT_SUB_TOPIC);
}
