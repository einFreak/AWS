
#include "MoistureShield.h"
#include "ESP8266_DRIVER.h"
#include "mqtt.h"

void ShieldSetup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(mA0, OUTPUT);
  pinMode(mA1, OUTPUT);
  pinMode(EN, OUTPUT);
  delay(100);
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(mA0, LOW);
  digitalWrite(mA1, LOW);
  digitalWrite(EN, LOW);
  delay(100);
}

int changeInput(char input) {
  digitalWrite(EN, HIGH);

  switch (input) {
    case 1:
      digitalWrite(mA0, LOW);
      digitalWrite(mA1, LOW);
      break;
    case 2:
      digitalWrite(mA0, HIGH);
      digitalWrite(mA1, LOW);
      break;
    case 3:
      digitalWrite(mA0, LOW);
      digitalWrite(mA1, HIGH);
      break;
    case 4:
      digitalWrite(mA0, HIGH);
      digitalWrite(mA1, HIGH);
      break;
    default:
      digitalWrite(EN, LOW);
      return 666;
      break;
  }
  delay(1000);
  return 0;
}



int read_moist(int *val, char sensor) {

  if (!changeInput(sensor)) {
    val[sensor - 1] = analogRead(0);
    return 0;
  }
  return 666;
}

int send_moist(int *val, char sensor) {

  if(!read_moist(val, sensor) ) {
    int moist_rel_pct = val[sensor - 1] - 460;
    int percentage = 100 - ( (moist_rel_pct * 100) / 540 ); //540 = moist_100_pct = 1000 - 460
    
    switch (sensor) {
        case 1:
          send_message("plants/1/debug/m_val", val[sensor - 1] );
          send_message("plants/1/hum", percentage);
          break;
        case 2:
          send_message("plants/2/debug/m_val", val[sensor - 1] );
          send_message("plants/2/hum", percentage);
          break;
        case 3:
          send_message("plants/3/debug/m_val", val[sensor - 1] );
          send_message("plants/3/hum", percentage);
          break;
        case 4:
          send_message("plants/4/debug/m_val", val[sensor - 1] );
          send_message("plants/4/hum", percentage);
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

int water_plant(char PumpNr, int water_time) {
  switch (PumpNr) {
        case 1:
          digitalWrite(D0, HIGH);
          delay(water_time);
          digitalWrite(D0, LOW);
          break;
        case 2:
          digitalWrite(D1, HIGH);
          delay(water_time);
          digitalWrite(D1, LOW);
          break;
        case 3:
          digitalWrite(D2, HIGH);
          delay(water_time);
          digitalWrite(D2, LOW);
          break;
        case 4:
          digitalWrite(D3, HIGH);
          delay(water_time);
          digitalWrite(D3, LOW);
          break;
        case 5:
          digitalWrite(D4, HIGH);
          delay(water_time);
          digitalWrite(D4, LOW);
          break;
        case 6:
          digitalWrite(D5, HIGH);
          delay(water_time);
          digitalWrite(D5, LOW);
          break;
        case 12:
          digitalWrite(D0, HIGH);
          digitalWrite(D1, HIGH);
          delay(water_time);
          digitalWrite(D0, LOW);
          digitalWrite(D1, LOW);
          break;
        case 13:
          digitalWrite(D0, HIGH);
          digitalWrite(D2, HIGH);
          delay(water_time);
          digitalWrite(D0, LOW);
          digitalWrite(D2, LOW);
          break;
        case 14:
          digitalWrite(D0, HIGH);
          digitalWrite(D3, HIGH);
          delay(water_time);
          digitalWrite(D0, LOW);
          digitalWrite(D3, LOW);
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
  send_message("debug", "Start Auto_Watering");
  int read_val;
  char water_counter = 0;
  send_message("debug", "Water Time Setting:");
  send_message("debug", 10000);
  //Smaller value stands for higher moisture
  if(!read_moist(val, sensor) ) {
    read_val = val[sensor -1 ];
    while (read_val > MOIST_MIN ){
      water_plant(PumpNr, 10000);
      water_counter++;
      delay(CONTROLER_TIME);
      send_moist(val, sensor);
      read_val = val[sensor -1 ];
    }
  }
  send_message("debug", "Watering amount:");
  send_message("debug", water_counter);
  
  if (read_val < MOIST_MAX) {
    send_message("error", "Too much water in Plant:");
    send_message("error", sensor);
  }
  send_message("debug", "End Auto_Watering");
}
