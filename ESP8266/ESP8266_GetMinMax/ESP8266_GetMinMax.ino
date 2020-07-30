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
unsigned int moist_min[4] = {2000, 2000 ,2000 ,2000};
unsigned int moist_max[4] = {0, 0 ,0 ,0};
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

    //reading values 1-3
    for (int i = 1; i < 4; i++) {
      send_message("debug/reading", i);
      send_moist(moist_val, i);

      if (moist_val[i] < moist_min[i])
        moist_min[i] = moist_val[i];
      if (moist_val[i] > moist_max[i])
        moist_max[i] = moist_val[i];

      send_message("plant1/debug/m_min", moist_min[i] );
      send_message("plant1/debug/m_max", moist_max[i] );
      
    }
    
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
