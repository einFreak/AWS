#ifndef BMP280_H
#define BMP280_H

#include <Wire.h>
#include <SPI.h>
#include "mqtt.h"
#include "Adafruit_BMP280.h"


Adafruit_BMP280 bmp; // I2C

void setup_bmp() {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));
  // 0x76 = I2C address, 0x58 = DefaultChipID
  if (!bmp.begin(0x76, 0x58)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

float get_bmp_temp() {
  
  float temp = bmp.readTemperature();
	float pres = bmp.readPressure();
	float alti = bmp.readAltitude(1021);
		
	Serial.print(F("Temperature = "));
  Serial.print(temp);
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(alti);
  Serial.println(" Pa");

  Serial.print(F("Approx altitude = "));
  Serial.print(alti); /* Adjusted to local forecast! */
  Serial.println(" m");

  Serial.println();

  send_message("plants/1/debug/temp", temp );
	send_message("plants/1/debug/pres", pres );
	send_message("plants/1/debug/alti", alti );
  send_message("plants/1/temp", temp);
	
	return temp;
}

#endif
