/* Shield Settings:
   D0 -> Verbraucher 0      D5 -> Verbraucher 5   |  A1 | A0  ->  Input
   D1 -> Verbraucher 1      D6 -> A0 Multiplexer  |   0 | 0   ->  A0
   D2 -> Verbraucher 2      D7 -> A1 Multiplexer  |   0 | 1   ->  A1
   D3 -> Verbraucher 3      D8 -> En Multiplexer  |   1 | 0   ->  A2 
   D4 -> Verbraucher 4                            |   1 | 1   ->  A3
*/

#ifndef MoistureShield_h
#define MoistureShield_h

#include "mqtt.h"
#define D0  16
#define D1  5
#define D2  4
#define D3  0
#define D4  2
#define D5  14
#define mA0 12
#define mA1 13
#define EN  15

int read_moist(int *val, int sensor);
int changeInput(int input);
void ShieldSetup();

void ShieldSetup() {
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);
  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);
  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);
  pinMode(D4, OUTPUT);
  digitalWrite(D4, LOW);
  pinMode(D5, OUTPUT);
  digitalWrite(D5, LOW);
  pinMode(mA0, OUTPUT);
  digitalWrite(mA0, LOW);
  pinMode(mA1, OUTPUT);
  digitalWrite(mA1, LOW);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
}

int changeInput(int input) {
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



int read_moist(int *val, int sensor) {

  if (!changeInput(sensor)) {

    val[sensor - 1] = analogRead(0);
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
}

#endif MoistureShield_h
