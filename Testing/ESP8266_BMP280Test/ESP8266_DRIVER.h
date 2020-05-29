#ifndef ESP8266_DRIVER_H
#define ESP8266_DRIVER_H



/* Shield Settings:
   D0 -> Verbraucher 0      D5 -> Verbraucher 5   |  A1 | A0  ->  Input
   D1 -> Verbraucher 1      D6 -> A0 Multiplexer  |   0 | 0   ->  A0
   D2 -> Verbraucher 2      D7 -> A1 Multiplexer  |   0 | 1   ->  A1
   D3 -> Verbraucher 3      D8 -> En Multiplexer  |   1 | 0   ->  A2 
   D4 -> Verbraucher 4                            |   1 | 1   ->  A3

   D2: LED, D3/4 no pull low, D8 no pull high
*/

#define D0  16
#define D1  5
#define D2  4
#define D3  0
#define D4  2
#define D5  14
#define mA0 12
#define mA1 13
#define EN  15


#endif ESP8266_DRIVER_H