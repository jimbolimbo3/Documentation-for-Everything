/*
 HTU21D Humidity Sensor Library
 By: Wesley Wong

 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 This library allows an Arduino to read from the HTU21D low-cost high-precision humidity sensor by software I2C.

 Software:
 Call HTU21D.Begin() in setup.

 HTU21D.ReadFirstHumidity() will return a float containing the humidity by the first sensor.
 HTU21D.ReadFirstTemperature() will return a float containing the temperature in Celsius by the first sensor.

 HTU21D.ReadSecondHumidity() will return a float containing the humidity by the second sensor.
 HTU21D.ReadSecondTemperature() will return a float containing the temperature in Celsius by the second sensor.

 HTU21D.ReadThirdHumidity() will return a float containing the humidity by the third sensor.
 HTU21D.ReadThirdTemperature() will return a float containing the temperature in Celsius by the third sensor.

 HTU21D.ReadFourthHumidity() will return a float containing the humidity by the fourth sensor.
 HTU21D.ReadFourthTemperature() will return a float containing the temperature in Celsius by the fourth sensor.
 */

#include "SoftI2C_HTU21D.h"
#include <SoftI2CMaster.h>

#if defined(ARDUINO) && ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

HTU21D::HTU21D()
{
  //Set initial values for private vars
}

//Begin
/****************************************************************************************************************/
//Config pins for software i2c communication
bool HTU21D::begin(void)
{
}


//Read the humidity
/**************************************************************************************************************/
//Calc humidity and return it to the user
float HTU21D::readFirstHumidity(void)
{
	SoftI2CMaster i2c1 = SoftI2CMaster( sdaPin1, sclPin1 );
	byte hLow, hHigh, checkSum;

	//Request a humidity reading
	i2c1.beginTransmission(HTU21D_ADDR);
	i2c1.send(TRIGGER_HUMD_MEASURE_NOHOLD);	////Measure humidity with no bus holding

	//Hang out while measurement is taken. Delay 50ms min, page 4 of datasheet.
	delay(55);

	//Comes back in three bytes, data(MSB) / data(LSB) / Checksum
	i2c1.requestFrom(HTU21D_ADDR);

	//Receive msb, lsb and checksum
	hHigh=i2c1.receive(false);
	hLow=i2c1.receive(false);
	checkSum=i2c1.receive(true);
	i2c1.endTransmission();
  
	unsigned int rawHumidity = ((unsigned int) hHigh << 8) | (unsigned int) hLow;
	rawHumidity &= 0xFFFC; //Zero out the status bits but keep them in place
  
	//Given the raw humidity data, calculate the actual relative humidity
	float tempRH = rawHumidity / (float)65536; //2^16 = 65536
	float rh = -6 + (125 * tempRH); //From page 14

	if(rh>100)
		rh=100;

	if(rh<0)
		rh=0;
  
	return rh;
}

float HTU21D::readSecondHumidity(void)
{
	SoftI2CMaster i2c2 = SoftI2CMaster( sdaPin2, sclPin2 );
	byte hLow, hHigh, checkSum;

	//Request a humidity reading
	i2c2.beginTransmission(HTU21D_ADDR);
	i2c2.send(TRIGGER_HUMD_MEASURE_NOHOLD);	////Measure humidity with no bus holding

	//Hang out while measurement is taken. Delay 50ms min, page 4 of datasheet.
	delay(55);

	//Comes back in three bytes, data(MSB) / data(LSB) / Checksum
	i2c2.requestFrom(HTU21D_ADDR);

	//Receive msb, lsb and checksum
	hHigh=i2c2.receive(false);
	hLow=i2c2.receive(false);
	checkSum=i2c2.receive(true);
	i2c2.endTransmission();
  
	unsigned int rawHumidity = ((unsigned int) hHigh << 8) | (unsigned int) hLow;
	rawHumidity &= 0xFFFC; //Zero out the status bits but keep them in place
  
	//Given the raw humidity data, calculate the actual relative humidity
	float tempRH = rawHumidity / (float)65536; //2^16 = 65536
	float rh = -6 + (125 * tempRH); //From page 14

	if(rh>100)
		rh=100;

	if(rh<0)
		rh=0;
  
	return rh;
}

float HTU21D::readThirdHumidity(void)
{
	SoftI2CMaster i2c3 = SoftI2CMaster( sdaPin3, sclPin3 );
	byte hLow, hHigh, checkSum;

	//Request a humidity reading
	i2c3.beginTransmission(HTU21D_ADDR);
	i2c3.send(TRIGGER_HUMD_MEASURE_NOHOLD);	////Measure humidity with no bus holding

	//Hang out while measurement is taken. Delay 50ms min, page 4 of datasheet.
	delay(55);

	//Comes back in three bytes, data(MSB) / data(LSB) / Checksum
	i2c3.requestFrom(HTU21D_ADDR);

	//Receive msb, lsb and checksum
	hHigh=i2c3.receive(false);
	hLow=i2c3.receive(false);
	checkSum=i2c3.receive(true);
	i2c3.endTransmission();
  
	unsigned int rawHumidity = ((unsigned int) hHigh << 8) | (unsigned int) hLow;
	rawHumidity &= 0xFFFC; //Zero out the status bits but keep them in place
  
	//Given the raw humidity data, calculate the actual relative humidity
	float tempRH = rawHumidity / (float)65536; //2^16 = 65536
	float rh = -6 + (125 * tempRH); //From page 14

	if(rh>100)
		rh=100;

	if(rh<0)
		rh=0;
  
	return rh;
}

float HTU21D::readFourthHumidity(void)
{
	SoftI2CMaster i2c4 = SoftI2CMaster( sdaPin4, sclPin4 );
	byte hLow, hHigh, checkSum;

	//Request a humidity reading
	i2c4.beginTransmission(HTU21D_ADDR);
	i2c4.send(TRIGGER_HUMD_MEASURE_NOHOLD);	////Measure humidity with no bus holding

	//Hang out while measurement is taken. Delay 50ms min, page 4 of datasheet.
	delay(55);

	//Comes back in three bytes, data(MSB) / data(LSB) / Checksum
	i2c4.requestFrom(HTU21D_ADDR);

	//Receive msb, lsb and checksum
	hHigh=i2c4.receive(false);
	hLow=i2c4.receive(false);
	checkSum=i2c4.receive(true);
	i2c4.endTransmission();
  
	unsigned int rawHumidity = ((unsigned int) hHigh << 8) | (unsigned int) hLow;
	rawHumidity &= 0xFFFC; //Zero out the status bits but keep them in place
  
	//Given the raw humidity data, calculate the actual relative humidity
	float tempRH = rawHumidity / (float)65536; //2^16 = 65536
	float rh = -6 + (125 * tempRH); //From page 14

	if(rh>100)
		rh=100;

	if(rh<0)
		rh=0;
  
	return rh;
}

//Read the temperature
/**************************************************************************************************************/
//Calc temperature and return it to the user
float HTU21D::readFirstTemperature(void)
{
	SoftI2CMaster i2c1 = SoftI2CMaster( sdaPin1, sclPin1 );
	byte tLow, tHigh, checkSum;

	//Request the temperature
	i2c1.beginTransmission(HTU21D_ADDR);
	i2c1.send(TRIGGER_TEMP_MEASURE_NOHOLD);

	//Hang out while measurement is taken. 50ms max, page 4 of datasheet.
	delay(55);

	//Comes back in three bytes, data(MSB) / data(LSB) / Checksum
	i2c1.requestFrom(HTU21D_ADDR);

	//Receive msb, lsb and checksum
	tHigh=i2c1.receive(false);
	tLow=i2c1.receive(false);
	checkSum=i2c1.receive(true);
	i2c1.endTransmission();
  
	unsigned int rawTemp = ((unsigned int) tHigh <<8) | (unsigned int) tLow;
	rawTemp &= 0xFFFC;

	//Given the raw tempuerature data, calculate the actual relative tempuerature
	float temp = rawTemp/(float)65536;
	float realTemp = -46.85 + (175.72 * temp);
  
	return realTemp;
}

float HTU21D::readSecondTemperature(void)
{
	SoftI2CMaster i2c2 = SoftI2CMaster( sdaPin2, sclPin2 );
	byte tLow, tHigh, checkSum;
	
	//Request the temperature
	i2c2.beginTransmission(HTU21D_ADDR);
	i2c2.send(TRIGGER_TEMP_MEASURE_NOHOLD);

	//Hang out while measurement is taken. 50ms max, page 4 of datasheet.
	delay(55);

	//Comes back in three bytes, data(MSB) / data(LSB) / Checksum
	i2c2.requestFrom(HTU21D_ADDR);

	//Receive msb, lsb and checksum
	tHigh=i2c2.receive(false);
	tLow=i2c2.receive(false);
	checkSum=i2c2.receive(true);
	i2c2.endTransmission();
  
	unsigned int rawTemp = ((unsigned int) tHigh <<8) | (unsigned int) tLow;
	rawTemp &= 0xFFFC;
	
	//Given the raw tempuerature data, calculate the actual relative tempuerature
	float temp = rawTemp/(float)65536;
	float realTemp = -46.85 + (175.72 * temp);
  
	return realTemp;
}

float HTU21D::readThirdTemperature(void)
{
	SoftI2CMaster i2c3 = SoftI2CMaster( sdaPin3, sclPin3 );
	byte tLow, tHigh, checkSum;
	
	//Request the temperature
	i2c3.beginTransmission(HTU21D_ADDR);
	i2c3.send(TRIGGER_TEMP_MEASURE_NOHOLD);

	//Hang out while measurement is taken. 50ms max, page 4 of datasheet.
	delay(55);

	//Comes back in three bytes, data(MSB) / data(LSB) / Checksum
	i2c3.requestFrom(HTU21D_ADDR);

	//Receive msb, lsb and checksum
	tHigh=i2c3.receive(false);
	tLow=i2c3.receive(false);
	checkSum=i2c3.receive(true);
	i2c3.endTransmission();
  
	unsigned int rawTemp = ((unsigned int) tHigh <<8) | (unsigned int) tLow;
	rawTemp &= 0xFFFC;
	
	//Given the raw tempuerature data, calculate the actual relative tempuerature
	float temp = rawTemp/(float)65536;
	float realTemp = -46.85 + (175.72 * temp);
  
	return realTemp;
}

float HTU21D::readFourthTemperature(void)
{
	SoftI2CMaster i2c4 = SoftI2CMaster( sdaPin4, sclPin4 );
	byte tLow, tHigh, checkSum;
	
	//Request the temperature
	i2c4.beginTransmission(HTU21D_ADDR);
	i2c4.send(TRIGGER_TEMP_MEASURE_NOHOLD);

	//Hang out while measurement is taken. 50ms max, page 4 of datasheet.
	delay(55);

	//Comes back in three bytes, data(MSB) / data(LSB) / Checksum
	i2c4.requestFrom(HTU21D_ADDR);

	//Receive msb, lsb and checksum
	tHigh=i2c4.receive(false);
	tLow=i2c4.receive(false);
	checkSum=i2c4.receive(true);
	i2c4.endTransmission();
  
	unsigned int rawTemp = ((unsigned int) tHigh <<8) | (unsigned int) tLow;
	rawTemp &= 0xFFFC;
	
	//Given the raw tempuerature data, calculate the actual relative tempuerature
	float temp = rawTemp/(float)65536;
	float realTemp = -46.85 + (175.72 * temp);
  
	return realTemp;
}