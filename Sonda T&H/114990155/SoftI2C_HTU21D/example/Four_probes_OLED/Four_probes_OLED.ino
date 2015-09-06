/******************************************************************************************************************

 HTU21D Humidity Sensor (Using SoftI2C)
 By: Wesley Wong

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


#include <U8glib.h>  //include u8g header for OLED display
#include <SoftI2CMaster.h>
#include "SoftI2C_HTU21D.h"

//constructor calls for I2C 128x64(col2-col129) SSD1306
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

//Create an instance of the object
HTU21D myMeasure;

int input_status1=0;
int input_status2=0;
int input_status3=0;
int input_status4=0;

int check(float data1, float data2)
{  
  if(data1>99 && data2>125)
    return 0;
  else
    return 1;
}

void drawHT(float humid1, float humid2, float humid3, float humid4, float tempC1, float tempC2, float tempC3, float tempC4)
{
  int test1=0;
  int test2=0;
  int test3=0;
  int test4=0;
  
  test1=check(humid1, tempC1);
  test2=check(humid2, tempC2);
  test3=check(humid3, tempC3);
  test4=check(humid4, tempC4);
  
  input_status1 = test1;
  input_status2 = test2;
  input_status3 = test3;
  input_status4 = test4;
    
  u8g.setFont(u8g_font_6x10);
  u8g.drawStr(5,10,"Probe Shield Test");

  if(test1==1)
  {
    //First Sensor
    u8g.drawStr(5,25,"1: ");
    u8g.setPrintPos(22,25);
    u8g.print(humid1);
    u8g.drawStr(50,25," %");
    u8g.setPrintPos(75,25);
    u8g.print(tempC1);
    u8g.drawStr(105,25," C");
  }
  else
  {
    u8g.drawStr(5,25,"1: ");
    u8g.drawStr(22,25,"No probe detected");
  }
  
  
  if(test2==1)
  {
    //Second Sensor
    u8g.drawStr(5,35,"2: ");
    u8g.setPrintPos(22,35);
    u8g.print(humid2);
    u8g.drawStr(50,35," %");
    u8g.setPrintPos(75,35);
    u8g.print(tempC2);
    u8g.drawStr(105,35," C");
  }
  else
  {
    u8g.drawStr(5,35,"2: ");
    u8g.drawStr(22,35,"No probe detected");
  }
  
  
  if(test3==1)
  {
    //Third Sensor
    u8g.drawStr(5,45,"3: ");
    u8g.setPrintPos(22,45);
    u8g.print(humid3);
    u8g.drawStr(50,45," %");
    u8g.setPrintPos(75,45);
    u8g.print(tempC3);
    u8g.drawStr(105,45," C");
  }
  else
  {
    u8g.drawStr(5,45,"3: ");
    u8g.drawStr(22,45,"No probe detected");
  }
    
  
  if(test4==1)
  {
    //Fourth Sensor
    u8g.drawStr(5,55,"4: ");
    u8g.setPrintPos(22,55);
    u8g.print(humid4);
    u8g.drawStr(50,55," %");
    u8g.setPrintPos(75,55);
    u8g.print(tempC4);
    u8g.drawStr(105,55," C");
  }
  else
  {
    u8g.drawStr(5,55,"4: ");
    u8g.drawStr(22,55,"No probe detected");
  }

}

void setup() {
  myMeasure.begin();
}

void loop() {
  float humid1 = myMeasure.readFirstHumidity();
  float humid2 = myMeasure.readSecondHumidity();
  float humid3 = myMeasure.readThirdHumidity();
  float humid4 = myMeasure.readFourthHumidity();
  
  float t1 = myMeasure.readFirstTemperature();
  float t2 = myMeasure.readSecondTemperature();
  float t3 = myMeasure.readThirdTemperature();
  float t4 = myMeasure.readFourthTemperature();
  
  int temp1=input_status1;
  int temp2=input_status2;
  int temp3=input_status3;
  int temp4=input_status4;
  
  // picture loop
  u8g.firstPage();  
  do {
    drawHT(humid1, humid2, humid3, humid4, t1, t2, t3, t4);
  } while( u8g.nextPage() );
  delay(1000);
  
  //If probe is plugged in, restart the OLED.
  if(temp1>input_status1|temp1<input_status1|temp2>input_status2|temp2<input_status2|temp3>input_status3|temp3<input_status3|temp4>input_status4|temp4<input_status4)
    u8g.begin();
}
