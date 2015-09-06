/* 
 HTU21D Humidity Sensor Library (SoftI2C)
 By: Wesley Wong

 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 Get humidity and temperature from the HTU21D sensor using software I2C.
 */

#if defined(ARDUINO) && ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <SoftI2CMaster.h>

//define pin for SCL (share SCL)
const byte sclPin1 = 7;
const byte sclPin2 = 7;
const byte sclPin3 = 7;
const byte sclPin4 = 7;

//define pins for SDA
const byte sdaPin1 = 5;
const byte sdaPin2 = 4;
const byte sdaPin3 = 3;
const byte sdaPin4 = 2;

#define HTU21D_ADDR 0x40  //Unshifted 7-bit I2C address for the sensor

#define TRIGGER_TEMP_MEASURE_HOLD  0xE3
#define TRIGGER_HUMD_MEASURE_HOLD  0xE5
#define TRIGGER_TEMP_MEASURE_NOHOLD  0xF3
#define TRIGGER_HUMD_MEASURE_NOHOLD  0xF5
#define WRITE_USER_REG  0xE6
#define READ_USER_REG  0xE7
#define SOFT_RESET  0xFE

class HTU21D
{
	public:
		HTU21D();

		//public function
		bool begin(void);
		float readFirstHumidity(void);
		float readSecondHumidity(void);
		float readThirdHumidity(void);
		float readFourthHumidity(void);
		float readFirstTemperature(void);
		float readSecondTemperature(void);
		float readThirdTemperature(void);
		float readFourthTemperature(void);
};

