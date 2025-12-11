/*
 * reference
 * sps30
 * https://github.com/WhyKickAmooCow/arduino-sps
 * i2c multiplexer
 * https://github.com/alvaroferran/I2C-multiplexer/blob/master/Library/I2CMux/examples/I2CMux_Example.ino
 * 
 * SPS30 I2C address = 0x69
 * TCA9548A I2C address = 0x70
 * 
 * TCA9548A analogPin
 * A0 --- GND(0)
 * A1 --- GND(0)
 * A2 --- GND(0)
 */
#define I2CMux_ADDR 0x70 
I2CMux mux(I2CMux_ADDR);

SPS30 sps30;
SPS30 SPS30_1;
SPS30 SPS30_2;
SPS30 SPS30_3;

int SPS30_1Pin = 0;
int SPS30_2Pin = 1;
int SPS30_3Pin = 2;

boolean en0 = true;
boolean en1 = true;
boolean en2 = true;
boolean en3 = true;

void initSPS30(){
  if(en1){
    //Serial.println("initSPS30_1");
    mux.switchToBus(SPS30_1Pin);
    SPS30_1.begin();
    delay(1000);
  }

  if(en2){
    //Serial.println("initSPS30_2");
    mux.switchToBus(SPS30_2Pin);
    SPS30_2.begin();
    delay(1000);
  }
  
  if(en3){
    //Serial.println("initSPS30_3");
    mux.switchToBus(SPS30_3Pin);
    SPS30_3.begin();
    delay(1000);    
  }
}
/*
void readSPS30(){
  readSPS30_1();
  readSPS30_2();
  readSPS30_3();
}
*/
void readSPS30_1(){
  if(en1){
    mux.switchToBus(SPS30_1Pin);
    if (SPS30_1.dataAvailable()){    
      float mass_concen[4];
      SPS30_1.getMass(mass_concen);
  
      float num_concen[5];
      SPS30_1.getNum(num_concen);
  
      char *pm[5] = {"PM0.5", "PM1.0", "PM2.5", "PM4.0", "PM10"};
  
      Sensor.SPS1.dust25 = mass_concen[1]; //소스이상 확인한바 PM 2.5 맞음
      Sensor.SPS1.dust10 = mass_concen[3]; //소스이상 확인한바 PM 10  맞음

      //filtering      
      Sensor.SPS1.dust25              = normalFilter1(Sensor.SPS1.dust25);      
      Sensor.SPS1.dust25_aveSmooth    = averageFilter(Sensor.SPS1.dust25);
      Sensor.SPS1.dust25_expoSmooth   = exponentFilter(Sensor.SPS1.dust25);            
      Sensor.SPS1.dust25_medianKalman = medianKalmanFilter1(Sensor.SPS1.dust25);      
    }        
  }
}

void readSPS30_2(){
  if(en2){
    mux.switchToBus(SPS30_2Pin);
    
    if (SPS30_2.dataAvailable()){         
      float mass_concen[4];
      SPS30_2.getMass(mass_concen);
  
      float num_concen[5];
      SPS30_2.getNum(num_concen);
  
      char *pm[5] = {"PM0.5", "PM1.0", "PM2.5", "PM4.0", "PM10"};
  
      Sensor.SPS2.dust25 = mass_concen[1]; //후에 보정값으로 수정
      Sensor.SPS2.dust10 = mass_concen[3];

      //filtering
      Sensor.SPS2.dust25              = normalFilter2(Sensor.SPS2.dust25);      
      Sensor.SPS2.dust25_aveSmooth    = averageFilter(Sensor.SPS2.dust25);
      Sensor.SPS2.dust25_expoSmooth   = exponentFilter(Sensor.SPS2.dust25);            
      Sensor.SPS2.dust25_medianKalman = medianKalmanFilter2(Sensor.SPS2.dust25);  
      
    }
  }
}

void readSPS30_3(){
  if(en3){    
    mux.switchToBus(SPS30_3Pin);
    
    if (SPS30_3.dataAvailable()){    
      float mass_concen[4];
      SPS30_3.getMass(mass_concen);
  
      float num_concen[5];
      SPS30_3.getNum(num_concen);
  
      char *pm[5] = {"PM0.5", "PM1.0", "PM2.5", "PM4.0", "PM10"};
  
      Sensor.SPS3.dust25 = mass_concen[1]; //후에 보정값으로 수정
      Sensor.SPS3.dust10 = mass_concen[3];

      //filtering
      Sensor.SPS3.dust25              = normalFilter3(Sensor.SPS3.dust25);      
      Sensor.SPS3.dust25_aveSmooth    = averageFilter(Sensor.SPS3.dust25);
      Sensor.SPS3.dust25_expoSmooth   = exponentFilter(Sensor.SPS3.dust25);            
      Sensor.SPS3.dust25_medianKalman = medianKalmanFilter3(Sensor.SPS3.dust25);    
    } 
  }
}



//------------------single-----------------
void initSPS30_0(){
  if(en0){
    Serial.println("initSPS30");
    sps30.begin();
    delay(1000);
  }
}

void readSPS30_0(){
  if(en0){
    print0();
    //delay(1000);  
  }
}

void print0(){  
  if (sps30.dataAvailable()){    
    Serial.println("------------sensor-------------------");
    Serial.println("0");
    float mass_concen[4];
    sps30.getMass(mass_concen);

    float num_concen[5];
    sps30.getNum(num_concen);

    char *pm[5] = {"PM0.5", "PM1.0", "PM2.5", "PM4.0", "PM10"};

    Serial.println("--- Mass Concentration ---");

    for (int i = 0; i < 4; i++){
      //Serial.printf("%s: %.2f\n", pm[i + 1], mass_concen[i]);
      Serial.print(pm[i+1]);
      Serial.print(" : ");
      Serial.println(mass_concen[i]);
    }   
  }
}
