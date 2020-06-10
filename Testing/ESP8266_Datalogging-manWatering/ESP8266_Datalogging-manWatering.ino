#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "NetworkInfo.h"
#include "mqtt.h"
#include "MoistureShield.h"
#include "AutoWatering.h"
#include "BMP280.h"

/*
 * moved to NetworkInfo.h
 * const char*   SSID            = "NETZWERKNAME";
 * const char*   PASSWORD        = "NETZWERKSCHLÜSSEL"; 
 */
int moist_val[4] = {0, 0 ,0 ,0};
void setup();
void loop();
void setup_wifi();
 
//Board starting setup
void setup() {
    ShieldSetup();
    setup_wifi();
    mqtt_Setup();
	  setup_bmp();
    digitalWrite(LED_BUILTIN, HIGH);
}

/*  
 *  loop running constantly on board, 
 *  call client.loop regulary to check for incomming messages
 */
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time msg were updated
// constants won't change:
const long interval = 30000; //30s

 
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

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
    	previousMillis = currentMillis;
    	get_bmp_temp();
    	delay(100);
    	send_moist(moist_val, 1);
      delay(100);
      send_message("plants/1/signal", WiFi.RSSI());
    }

    client.loop();        
}

//Connecting WIFI
void setup_wifi() {
    delay(10);
 
    WiFi.begin(SSID, PASSWORD);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}
