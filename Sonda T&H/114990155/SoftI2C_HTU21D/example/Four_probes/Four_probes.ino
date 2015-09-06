/******************************************************************************************************************

 HTU21D Humidity Sensor (Using SoftI2C)
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
 
 ****************************************************************************************************************/


#include <SoftI2CMaster.h>
#include "SoftI2C_HTU21D.h"


//Create an instance of the object
HTU21D myMeasure;

int check(float data1, float data2)
{
  if(data1>99 && data2>125)
    return 0;
  else
    return 1;
}

void setup() {
  Serial.begin(9600);
  Serial.println("SoftI2C_HTU21D Example...");
  
  myMeasure.begin();
}

void loop() {
  float humid1 = myMeasure.readFirstHumidity();
  float humid2 = myMeasure.readSecondHumidity();
  float humid3 = myMeasure.readThirdHumidity();
  float humid4 = myMeasure.readFourthHumidity();
  
  float temp1 = myMeasure.readFirstTemperature();
  float temp2 = myMeasure.readSecondTemperature();
  float temp3 = myMeasure.readThirdTemperature();
  float temp4 = myMeasure.readFourthTemperature();
  
  int test1=check(humid1, temp1);
  int test2=check(humid2, temp2);
  int test3=check(humid3, temp3);
  int test4=check(humid4, temp4);
  
  Serial.println("First sensor: ");
  if(test1==1)
  {
    Serial.print("Tempuature: ");
    Serial.print(temp1);
    Serial.print(" C     ");
    Serial.print("Humidity: ");
    Serial.print(humid1);
    Serial.println(" %");
  }
  else
  {
    Serial.println("No probe detected");
  }
  
  Serial.println("Second sensor: ");
  if(test2==1)
  {
    Serial.print("Tempuature: ");
    Serial.print(temp2);
    Serial.print(" C     ");
    Serial.print("Humidity: ");
    Serial.print(humid2);
    Serial.println(" %");
  }
  else
  {
    Serial.println("No probe detected");
  }
  
  Serial.println("Third sensor: ");
  if(test3==1)
  {
    Serial.print("Tempuature: ");
    Serial.print(temp3);
    Serial.print(" C     ");
    Serial.print("Humidity: ");
    Serial.print(humid3);
    Serial.println(" %");
  }
  else
  {
    Serial.println("No probe detected");
  }
  
  Serial.println("Fourth sensor: ");
  if(test4==1)
  {
    Serial.print("Tempuature: ");
    Serial.print(temp4);
    Serial.print(" C     ");
    Serial.print("Humidity: ");
    Serial.print(humid4);
    Serial.println(" %");
  }
  else
  {
    Serial.println("No probe detected");
  }
  
  Serial.println("");
  
  delay(5000);
}
