#ifndef AutoWatering_h
#define AutoWatering_h

#include "ESP8266_DRIVER.h"
#include "mqtt.h"
#include "MoistureShield.h"

//Smaller value stands for higher moisture
//prevents overwatering - fkt tbd
#define MOIST_MAX		400
//starting value to water
#define MOIST_MIN		600
#define WATER_TIME		5000
#define CONTROLER_TIME	10000


int send_moist	(int *val, char sensor);
int water_plant	(char PumpNr);



int send_moist(int *val, char sensor) {

  if(!read_moist(val, sensor) ) {
    int moist_rel_pct = val[sensor - 1] - 460;
    int percentage = 100 - ( (moist_rel_pct * 100) / 540 ); //540 = moist_100_pct = 1000 - 460
    
    switch (sensor) {
        case 1:
          send_message("plant1/debug/m_val", val[sensor - 1] );
          send_message("plant1/hum", percentage);
          break;
        case 2:
          send_message("plant2/debug/m_val", val[sensor - 1] );
          send_message("plant2/hum", percentage);
          break;
        case 3:
          send_message("plant3/debug/m_val", val[sensor - 1] );
          send_message("plant3/hum", percentage);
          break;
        case 4:
          send_message("plant4/debug/m_val", val[sensor - 1] );
          send_message("plant4/hum", percentage);
          break;
        default:
          send_message("debug", "No Sensor for this Input:");
          send_message("debug", sensor);
          return 666;
          break;
      }
    return 0;
  }
  return 666;
}

int water_plant(char PumpNr) {
	switch (PumpNr) {
        case 1:
          digitalWrite(D1, HIGH);
		  delay(WATER_TIME);
		  digitalWrite(D1, LOW);
          break;
        case 2:
          digitalWrite(D2, HIGH);
		  delay(WATER_TIME);
		  digitalWrite(D2, LOW);
		  break;
        case 3:
          digitalWrite(D3, HIGH);
		  delay(WATER_TIME);
		  digitalWrite(D3, LOW);
		  break;
        case 4:
          digitalWrite(D4, HIGH);
		  delay(WATER_TIME);
		  digitalWrite(D4, LOW);
		  break;
        default:
          send_message("debug", "No Motor for this Input:");
          send_message("debug", PumpNr);
          return 666;
          break;
    }
	return 0;
}

int Auto_Watering(int *val, char sensor, char PumpNr) {
	int read_val = 1000;
	char water_counter = 0;
	send_message("debug", "Water Time Setting:);
	send_message("debug", WATER_TIME);
	//Smaller value stands for higher moisture
	while (!read_moist(val, sensor) && read_val > MOIST_MIN ){
		read_val = val[sensor -1 ];
		water_plant(PumpNr);
		send_moist(val, sensor);
		water_counter++;
		delay(CONTROLER_TIME);
	}
	send_message("debug", "Watering amount:");
	send_message("debug", water_counter);
	
	if (read_val < MOIST_MAX) {
		send_message("error", "Too much water in Plant:");
		send_message("error", sensor);
	}
}


#endif AutoWatering_h
