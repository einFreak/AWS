#include <ESP8266WiFi.h>
#include "NetworkInfo.h"
#include "MoistureShield.h"
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
}

/*  
 *  loop running constantly on board, 
 *  call client.loop regulary to check for incomming messages
 */

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis1 = 0;        // will store last time msg were updated
unsigned long previousMillis2 = 0;
// constants won't change:
const long interval1 = 60*1000; //60s
const long interval2 = 60000*30; //30min

void loop() {
  //Check WiFi
  if (WiFi.status() != WL_CONNECTED) {
    setup_wifi();
  }
  
  //check mqtt status
  if (!MQTTclient.connected()) {
    MQTTreconnect();
  }
  MQTTclient.loop();
	
	unsigned long currentMillis = millis();
  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;
    get_bmp_temp();
    delay(100);
    send_moist(moist_val, 1);
    send_moist(moist_val, 2);
    delay(100);
    send_message("plants/1/signal", WiFi.RSSI());
  }

  /*
  //keep moisture over 25
  currentMillis = millis();
  
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;
    int percentage1 = 100 - ( ((moist_val[0] - 460) * 100) / 540 ); //540 = moist_100_pct = 1000 - 460
    int percentage2 = 100 - ( ((moist_val[1] - 460) * 100) / 540 ); //540 = moist_100_pct = 1000 - 460
      
    if (percentage1 < 35) {
      send_message("debug/watering", 30);
      water_plant(0, 30*1000);
    }
    if (percentage2 < 35) {
      send_message("debug/watering", 30);
      water_plant(3, 30*1000);
    }
  }*/

  MQTTclient.loop();
}

//Connecting WIFI
void setup_wifi() {
    delay(10);

    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}
