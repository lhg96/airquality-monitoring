#ifndef RA200_h
#define RA200_h

#include <Wire.h>    // I2C librarys
#include <SimpleTimer.h> // here is the SimpleTimer library
#include <SoftwareSerial.h>
#include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30
#include <SHT3x.h>
#include <SPS30.h>
#include <I2CMux.h>
#include <Adafruit_NeoPixel.h>
#include <RTClib.h>

#define I2C_SDA 25
#define I2C_SCL 26
#define TOUCH_PIN 27

const boolean  deb PROGMEM = true ; //developer mode
RTC_DS1307     RTC;
SimpleTimer    timer; 
SoftwareSerial radonSerial(16, 17);

typedef struct{
    float   dust10;
    float   dust25;    
}_sps30;

typedef struct{
    float dust10;
    float dust25;    
    float dust25_aveSmooth;
    float dust25_expoSmooth;
    float dust25_median;      //median
    float dust25_kalman;      //kalman
    float dust25_medianKalman;//median + kalman
}_sps1;

typedef struct{
    float dust10;
    float dust25;    
    float dust25_aveSmooth;
    float dust25_expoSmooth;
    float dust25_median;      //median
    float dust25_kalman;      //kalman
    float dust25_medianKalman;//median + kalman
}_sps2;

typedef struct{
    float dust10;
    float dust25;    
    float dust25_aveSmooth;
    float dust25_expoSmooth;
    float dust25_median;      //median
    float dust25_kalman;      //kalman
    float dust25_medianKalman;//median + kalman
}_sps3;

typedef struct{
    float Temp;
    float Humi;
}_sht;

typedef struct{
    int Tvoc;
    int Eco2;
}_sgp;

typedef struct{
    int   rou;
    int   unit;
    float rTime;
    float value;
}_rs9a;

typedef struct{
    _sps30  SPS; // callibration
    _sps1   SPS1;
    _sps2   SPS2;
    _sps3   SPS3;
    _sht    SHT;
    _sgp    SGP;
    _rs9a  RS9A;
}_sensor;


typedef struct{
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
}_time;

_sensor Sensor;
_time   Time;

#endif
