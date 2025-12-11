/*
 * I2C address = 0x44
 */

//SHT3x sht30; //RA200
 //OA100 
 
SHT3x sht30( 0x45,         //Set the address
               SHT3x::Zero,  //Functions will return zeros in case of error
               255,          //If you DID NOT connected RESET pin
               SHT3x::SHT30, //Sensor type
               SHT3x::Single_LowRep_ClockStretch //Low repetability mode
               );



void initSHT30() {
  sht30.Begin();
}

void readSHT30() {  
  sht30.UpdateData();
  
  Sensor.SHT.Temp = sht30.GetTemperature();
  Sensor.SHT.Humi = sht30.GetRelHumidity();

  strtemp = (String)Sensor.SHT.Temp;
  strhumi = (String)Sensor.SHT.Humi;

  //Serial.println("Temp:"+strtemp);
  //Serial.println("Humi:"+strhumi);
}
/*
#include "BME280.h"
BME280 bme(Wire,0x77);
void initSHT30(){
   if (bme.begin() < 0) {
      Serial.println("BME280 Error communicating with sensor.");
   } 
}
void readSHT30() {  
  // read the sensor
  bme.readSensor();
  Sensor.SHT.Temp = bme.getTemperature_C();
  Sensor.SHT.Humi   = bme.getHumidity_RH();  
  printBME280();
}

void printBME280(){  
   String strtemp = (String)Sensor.SHT.Temp;
   String strhumi = (String)Sensor.SHT.Humi;
    Serial.print("Temp: ");
    Serial.print(strtemp);
    Serial.print(" c\tHumi: ");
    Serial.print(strhumi);
    Serial.println(" %");  
}*/
