#ifndef MoistureShield_h
#define MoistureShield_h

//Smaller value stands for higher moisture
//prevents overwatering - fkt tbd
#define MOIST_MAX    630
//starting value to water
#define MOIST_MIN   860
#define CONTROLER_TIME  15000

int read_moist(int *val, char sensor);
int changeInput(int input);
void ShieldSetup();

int send_moist  (int *val, char sensor);
int water_plant (char PumpNr, int water_time);
int Auto_Watering(int *val, char sensor, char PumpNr);

#endif
