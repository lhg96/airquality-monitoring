#pragma once
#include "RA100.h"

//String strdust25_1;
//String strdust10_1;
//String strdust25_2;
//String strdust10_2;
//String strdust25_3;
//String strdust10_3;

String strtemp;
String strhumi;
String strtvoc;
String streco2;
String strradon;

void setup() {
  Serial.begin(19200);   
  Wire.begin(I2C_SDA, I2C_SCL);

  //initRTC();
  initWS2812();
  initRS9A();  
  initSGP30();
  initSHT30();
  initSPS30();
  initHTTM();
  initFilter();

  //timer.setInterval(1000L, readTime);
  timer.setInterval(1000L, dataout2);
  //timer.setInterval(1000L, plotter);
  timer.setInterval(1000L, runWS2812);
  timer.setInterval(5000L, readRS9A);
  timer.setInterval(5000L, readSGP30);
  timer.setInterval(1000L, readSHT30);
  timer.setInterval(1000L, readSPS30_1);
  timer.setInterval(1000L, readSPS30_2);
  timer.setInterval(5000L, readSPS30_3);

  
  headerPrint(); //header print
}

void loop() {
  timer.run();
  // readHTTM();
}
