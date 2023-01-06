#include <Wire.h>
#include "LiquidCrystal.h"
LiquidCrystal lcd(37, 36, 35, 34, 33, 32);

  #define _i2cAddress 0x60
  #define BEARING_Register 2 
  #define ONE_BYTE   1
  #define TWO_BYTES  2
  #define FOUR_BYTES 4
  #define SIX_BYTES  6

  byte _byteHigh;
  byte _byteLow;

  int nReceived;
  signed char roll;
  signed char pitch;

  int bearing;
  String dir;
  void setup() {

  Serial.begin(9600);

  // Initialize i2c
  Wire.begin();
  lcd.begin(16, 2);
  
}
void loop() {
   ReadCompass(); 
  Serial.print("CMP=");
  Serial.print(bearing);
  Serial.print(" degrees,");
  Serial.println();

  if(bearing <0 ){
  dir ="N";  
  }
  else if (bearing <45 ) {
  dir = "NE";
  }
  else if (bearing <90) {
  dir = "E";
  }
  else if (bearing <135 ) {
  dir = "SE";
  }
  else if (bearing <180) {
  dir = "S";
  }
  else if (bearing <225) {
  dir = "SW";
  }
  else if (bearing <270) {
  dir = "W";
  }
  else if (bearing <315) {
  dir = "NW";
  }
  lcd.setCursor(0, 1);
  //lcd.print(bearing);
  //lcd.print(" degrees");
  lcd.print(dir);
}
  int16_t getBearing()
{
  
  Wire.beginTransmission(_i2cAddress);


  Wire.write(BEARING_Register);

  int nackCatcher = Wire.endTransmission();


  if(nackCatcher != 0){return 0;}
  
 
  nReceived = Wire.requestFrom(_i2cAddress , TWO_BYTES);

  
  if (nReceived != TWO_BYTES) return 0;


  _byteHigh = Wire.read(); 
  _byteLow = Wire.read();

 
  bearing = ((_byteHigh<<8) + _byteLow) / 10;
  
  return bearing;
}

void ReadCompass()
{

  Wire.beginTransmission(_i2cAddress);

  Wire.write(BEARING_Register);

  int nackCatcher = Wire.endTransmission();

  if(nackCatcher != 0){bearing = 0; pitch = 0;  roll = 0; return;}

  nReceived = Wire.requestFrom(_i2cAddress , FOUR_BYTES);


  if (nReceived != FOUR_BYTES) {bearing = 0; pitch = 0;  roll = 0; return;}
  

  _byteHigh = Wire.read(); _byteLow = Wire.read();
  bearing = ((_byteHigh<<8) + _byteLow) / 10;


  pitch = Wire.read();




}
