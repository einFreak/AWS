#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "G:\AWS-Project\ESP8266_HumSens\NetworkInfo.h"

//Ausgelagert in Headerdatei
//const char*   SSID            = "NETZWERKNAME";
//const char*   PASSWORD        = "NETZWERKSCHLÜSSEL";
const char*     MQTT_BROKER_IP  = "192.168.178.190";
const char*     MQTT_SUB_TOPIC  = "/home/data"; //zB "/home/data" - momentan unnötig
int             MQTT_PORT       = 1883;
 
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int moist_val = 0;
int moist_max = moist_val;
int moist_min = moist_val;
 
//Eisntellungen bei Start des Boards
void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(MQTT_BROKER_IP, MQTT_PORT);  //Broker + Port setzen
    client.setCallback(callback);     //Fkt callback bei Nachrichtenempfang

    moist_val = analogRead(0);
    moist_max = moist_val;
    moist_min = moist_val;
}
 
void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(SSID);
 
    WiFi.begin(SSID, PASSWORD);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
 
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
 
void reconnect() {
    while (!client.connected()) {
        Serial.println("Verbindung mit MQTT wiederherstellen...");
        
    // Create a random client ID
    String clientId = "ESP8266_HumSens-";
    clientId += String(random(0xffff), HEX);
    
    //Verbindungsversuch - keine Nachricht bei Erfolg
    if (!client.connect(clientId.c_str())) {
            Serial.print("fehlgeschlagen, rc=");
            Serial.print(client.state());
            Serial.println(" neuer Versuch in 5 Sekunden");
            delay(5000);
        }
    }
    client.subscribe(MQTT_SUB_TOPIC);
    Serial.println("MQTT Connected...");
}

int read_moist() {
  moist_val = analogRead(0);
  
  if (moist_val > moist_max)
    moist_max = moist_val;
  if (moist_val < moist_min)
    moist_min = moist_val;

  int moist_100 = moist_max - moist_min;
  int moist_akt = moist_val - moist_min;

  send_message("plant1/debug/m_val", moist_val );
  send_message("plant1/debug/m_max", moist_max );
  send_message("plant1/debug/m_min", moist_min );
  
  int percentage = 100 - ( (moist_akt * 100) / moist_100 );
  return percentage;
}

//Läuft konstant am Board, client.loop regelmäßg aufrufen um eingehende Nachrichten zu verarbeiten. Gibt false bei Verbindungsabbruch aus.
void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
    
  
  
  send_message("plant1/hum", read_moist() );
  delay(5000);
}

//Aufruf bei Nachricht in Topic
void callback(char* topic, byte* payload, unsigned int length) {
    
  Serial.print("Neue Nachricht [");
    Serial.print(topic);
    Serial.print("] ");
  
  //erstelle msg-Array zur Verarbeitung
    char msg[length+1];
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
        msg[i] = (char)payload[i];
    }
    Serial.println();
  
  //End of line für fertigen String
    msg[length] = '\0';
    Serial.println(msg);
  
  //Hier Nachricht verarbeiten
    // if(strcmp(msg,"on")==0){
        // digitalWrite(13, HIGH);
    // }
    // else if(strcmp(msg,"off")==0){
        // digitalWrite(13, LOW);
    // }
}

void send_message(const char* topic, const char* payload) {
  client.publish(topic, payload);
}

void send_message(const char* topic, int payload) {
  char buffer[33];
  itoa(payload, buffer, 10);
  const char* p = buffer;
  client.publish(topic, p);
}
