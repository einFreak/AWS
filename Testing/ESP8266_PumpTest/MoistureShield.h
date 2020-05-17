#ifndef MoistureShield_h
#define MoistureShield_h

#include "ESP8266_DRIVER.h"

int read_moist(int *val, char sensor);
int changeInput(int input);
void ShieldSetup();

void ShieldSetup() {
  pinMode(D0, OUTPUT);
  digitalWrite(D0, LOW);
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

#endif MoistureShield_h
