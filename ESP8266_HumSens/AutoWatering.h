#ifndef AutoWatering_h
#define AutoWatering_h

#include "mqtt.h"
#include "MoistureShield.h"

int send_moist(int *val, int sensor);



int send_moist(int *val, int sensor) {

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




#endif AutoWatering_h
