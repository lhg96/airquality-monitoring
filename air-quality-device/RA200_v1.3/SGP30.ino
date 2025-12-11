/*
 * I2C address = 0x58
 */
SGP30 sgp30; //create an object of the SGP30 class

void initSGP30(){  
  if (sgp30.begin() == false) {
    Serial.println("No SGP30 Detected. Check connections.");
    //while (1); //mfix
  }
  sgp30.initAirQuality();
}

void readSGP30(){
  //First fifteen readings will be
  //CO2: 400 ppm  TVOC: 0 ppb  
  //measure CO2 and TVOC levels
  sgp30.measureAirQuality();

  Sensor.SGP.Tvoc = sgp30.TVOC;
  Sensor.SGP.Eco2 = sgp30.CO2;

  strtvoc = Sensor.SGP.Tvoc;
  streco2 = Sensor.SGP.Eco2;
  
}
