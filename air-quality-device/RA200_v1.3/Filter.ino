/*
 Kalman filter
 https://github.com/denyssene/SimpleKalmanFilter
 
 SimpleKalmanFilter(e_mea, e_est, q);
 e_mea: Measurement Uncertainty 
 e_est: Estimation Uncertainty 
 q: Process Noise

 Exponencial Filter
 https://github.com/luisllamasbinaburo/Arduino-SingleEmaFilter
 https://github.com/mrkaleArduinoLib/gbj_filter_exponential   x
 https://github.com/MattFryer/Smoothed

 median filter
 https://github.com/daPhoosa/MedianFilter
 https://github.com/luisllamasbinaburo/Arduino-MedianFilter
*/

//kalman
#include <SimpleKalmanFilter.h>
//exponential
#include <Smoothed.h>
//median
#include "MedianFilterLib.h"

SimpleKalmanFilter pm25KalmanFilter(1, 1, 0.1); //medianKalman Kalman 통합

Smoothed <float> aveFilter;
Smoothed <float> expoFilter;

MedianFilter<float> mediFilter1(5); //medianKalman
MedianFilter<float> mediFilter2(5); //medianKalman
MedianFilter<float> mediFilter3(5); //medianKalman

void initFilter(){
  aveFilter.begin(SMOOTHED_AVERAGE,15); //3x 배수
  expoFilter.begin(SMOOTHED_EXPONENTIAL, 15); //3x 배수
}
//------------------------------
float preValue1;
float normalFilter1(float value){  
  if(value<0|value>300){
    value = preValue1;
  }else{
    preValue1 = value;
  }
  return value;
}
float preValue2;
float normalFilter2(float value){  
  if(value<0|value>300){
    value = preValue2;
  }else{
    preValue2 = value;
  }
  return value;
}
float preValue3;
float normalFilter3(float value){  
  if(value<0|value>300){
    value = preValue3;
  }else{
    preValue3 = value;
  }
  return value;
}

//smoothing 3 in 1
float exponentFilter(float value){   
  expoFilter.add(value);
  return expoFilter.get();
}
float averageFilter(float value){  
  aveFilter.add(value);
  return aveFilter.get();
}

float medianKalmanFilter1(float value){  
  float newValue = mediFilter1.AddValue(value);
  newValue = pm25KalmanFilter.updateEstimate(newValue);
  return newValue;
}
float medianKalmanFilter2(float value){  
  float newValue = mediFilter2.AddValue(value);
  newValue = pm25KalmanFilter.updateEstimate(newValue);
  return newValue;
}
float medianKalmanFilter3(float value){  
  float newValue = mediFilter3.AddValue(value);
  newValue = pm25KalmanFilter.updateEstimate(newValue);
  return newValue;
}
