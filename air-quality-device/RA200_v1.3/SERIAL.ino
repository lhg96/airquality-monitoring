/**
 * 20200610
 * 출력용 코드
 */

 int const STANDARD      = 1; //PM2.5 raw data
 int const KALMAN        = 2; //PM2.5 raw data + kalman
 int const SINGLE_SMOOTH = 3; //PM2.5 single data + kalman + aveSmooth + expoSmooth
 int const SINGLE_KALMAN_MEDIAN = 4; //PM2.5 single data + kalman + median + median&kalman
 int const THREE_SMOOTH_KALMAN_MEDIAN = 5; //PM2.5 three data + average + exponential + median&kalman

 int outMode = 5; // 1 standard out 2 kalman with all , 3 single with kalman smooth
 
void dataout(){
    String strdust25_1 = String(Sensor.SPS1.dust25);  
    String strdust25_2 = String(Sensor.SPS2.dust25);  
    String strdust25_3 = String(Sensor.SPS3.dust25);
    String strdust10_1 = String(Sensor.SPS1.dust10);
    String strdust10_2 = String(Sensor.SPS2.dust10);
    String strdust10_3 = String(Sensor.SPS3.dust10);
  
    String sendMessage;
    sendMessage += "SPS1 | PM2.5 : " + strdust25_1 + "ug/m3   PM10 : " + strdust10_1 + "ug/m3   \n";
    sendMessage += "SPS2 | PM2.5 : " + strdust25_2 + "ug/m3   PM10 : " + strdust10_2 + "ug/m3   \n";
    sendMessage += "SPS3 | PM2.5 : " + strdust25_3 + "ug/m3   PM10 : " + strdust10_3 + "ug/m3   \n";
    sendMessage += "SHT  | TEMP  : " + strtemp + "°C   HUMI : " + strhumi + "%  \n";
    sendMessage += "SGP  | TVOC  : " + strtvoc + "ppb   ECO2 : " + streco2 + "ppm";

    Serial.println();
    Serial.println();
    Serial.println(sendMessage);
    Serial.println();
}


//---------------------------------------------------------------------------------
//미세먼지 테스트용 출력
//for filtering
void headerPrint(){
  String delim =",";
  Serial.println();
  String sendMessage ="";
    if(outMode==STANDARD){
      sendMessage += "SPS1|PM2.5";  
      sendMessage += delim +"SPS2|PM2.5";
      sendMessage += delim +"SPS3|PM2.5";
    }else if(outMode==KALMAN){    
      sendMessage += "SPS1|PM2.5" +delim+"SPS1|PM2.5_Kalman";  
      sendMessage += delim +"SPS2|PM2.5" +delim+"SPS2|PM2.5_Kalman";
      sendMessage += delim +"SPS3|PM2.5" +delim+"SPS3|PM2.5_Kalman";      
    }else if(outMode==SINGLE_SMOOTH){    
      sendMessage += "SPS1|PM2.5" +delim+"SPS1|PM2.5_Kalman";  
      sendMessage += delim +"SPS1|aveSmooth" +delim+"SPS1|ExpoSmooth";      
    }else if(outMode==SINGLE_KALMAN_MEDIAN){    
      sendMessage += "SPS1|PM2.5" +delim+"SPS1|PM2.5_Kalman";  
      sendMessage += delim +"SPS1|Median" +delim+"SPS1|Median&Kalman";          
    }else if(outMode==THREE_SMOOTH_KALMAN_MEDIAN){
      sendMessage += "SPS1|PM2.5" +delim+"SPS2|PM2.5"+delim+"SPS3|PM2.5";  
      sendMessage += delim +"Three|Average" +delim+"Three|Exponential" +delim+"Three|Median&Kalman";          
    }
  Serial.println(sendMessage);
}

void plotter(){
  String delim =",";
  String strdust25_1 = String(Sensor.SPS1.dust25);  
  String strdust25_2 = String(Sensor.SPS2.dust25);  
  String strdust25_3 = String(Sensor.SPS3.dust25);
  //kalman filter
  String strdust25_1_kalman = String(Sensor.SPS1.dust25_kalman);
  String strdust25_2_kalman = String(Sensor.SPS2.dust25_kalman);
  String strdust25_3_kalman = String(Sensor.SPS3.dust25_kalman);
  //aveSmooth 1
  String strdust25_1_aveSmooth = String(Sensor.SPS1.dust25_aveSmooth);
  //aveSmooth 3
  String strdust25_3_aveSmooth = String(Sensor.SPS3.dust25_aveSmooth);
  //expoSmooth 1
  String strdust25_1_expoSmooth = String(Sensor.SPS1.dust25_expoSmooth);
  //expoSmooth 3
  String strdust25_3_expoSmooth = String(Sensor.SPS3.dust25_expoSmooth);
  //median
  String strdust25_1_median = String(Sensor.SPS1.dust25_median);
  //medianKalman 1
  String strdust25_1_medianKalman = String(Sensor.SPS1.dust25_medianKalman);  
  //medianKalman 3
  String strdust25_3_medianKalman = String(Sensor.SPS3.dust25_medianKalman);  
  

  String sendMessage ="";  
  if(outMode==STANDARD){
    sendMessage += strdust25_1;
    sendMessage += delim+strdust25_2;
    sendMessage += delim+strdust25_3;    
  }else if(outMode==KALMAN){        
    sendMessage += strdust25_1 + delim + strdust25_1_kalman;
    sendMessage += delim+strdust25_2 + delim + strdust25_2_kalman ;
    sendMessage += delim+strdust25_3 + delim + strdust25_3_kalman;  
  }else if(outMode==SINGLE_SMOOTH){   
    sendMessage += strdust25_1;
    sendMessage += delim+strdust25_1_kalman;
    sendMessage += delim+strdust25_1_aveSmooth;
    sendMessage += delim+strdust25_1_expoSmooth;  
  }else if(outMode==SINGLE_KALMAN_MEDIAN){ //4   
    sendMessage += strdust25_1;
    sendMessage += delim+strdust25_1_kalman;
    sendMessage += delim+strdust25_1_median;    
    sendMessage += delim+strdust25_1_medianKalman;    
  }else if(outMode==THREE_SMOOTH_KALMAN_MEDIAN){
    sendMessage += strdust25_1;
    sendMessage += delim+strdust25_2;
    sendMessage += delim+strdust25_3;        
    sendMessage += delim+strdust25_3_aveSmooth;
    sendMessage += delim+strdust25_3_expoSmooth;    
    sendMessage += delim+strdust25_3_medianKalman;    
  }   
  Serial.println(sendMessage);
}

/**
 * 미세먼지 측정용
 */
void dataout2(){
    String delim =",";
    String strdust25_1 = String(Sensor.SPS1.dust25);  
    String strdust25_2 = String(Sensor.SPS2.dust25);  
    String strdust25_3 = String(Sensor.SPS3.dust25);
    String strdust10_1 = String(Sensor.SPS1.dust10);
    String strdust10_2 = String(Sensor.SPS2.dust10);
    String strdust10_3 = String(Sensor.SPS3.dust10);

    //kalman filter
    String strdust25_1_kalman = String(Sensor.SPS1.dust25_kalman);
    String strdust25_2_kalman = String(Sensor.SPS2.dust25_kalman);
    String strdust25_3_kalman = String(Sensor.SPS3.dust25_kalman);
    //aveSmooth 1
    String strdust25_1_aveSmooth = String(Sensor.SPS1.dust25_aveSmooth);
    //aveSmooth 3
    String strdust25_3_aveSmooth = String(Sensor.SPS3.dust25_aveSmooth);
    //expoSmooth 1
    String strdust25_1_expoSmooth = String(Sensor.SPS1.dust25_expoSmooth);
    //expoSmooth 3
    String strdust25_3_expoSmooth = String(Sensor.SPS3.dust25_expoSmooth);
    //median
    String strdust25_1_median = String(Sensor.SPS1.dust25_median);
    //medianKalman 1
    String strdust25_1_medianKalman = String(Sensor.SPS1.dust25_medianKalman);  
    //medianKalman 3
    String strdust25_3_medianKalman = String(Sensor.SPS3.dust25_medianKalman);  

    String strROU    = String(Sensor.RS9A.rou);
    String strUnit   = String(Sensor.RS9A.unit);
    String strRTime  = String(Sensor.RS9A.rTime);
    String strValue  = String(Sensor.RS9A.value);
    
    String sendMessage;  
    sendMessage = strtemp;//1
    sendMessage += delim+strhumi;//2
    sendMessage += delim+strtvoc;//3
    sendMessage += delim+streco2;//4

    sendMessage += delim+strROU;//5
    sendMessage += delim+strUnit;//6
    sendMessage += delim+strRTime;//7
    sendMessage += delim+strValue;//8
    //+ radon
    if(outMode==THREE_SMOOTH_KALMAN_MEDIAN){
      sendMessage += delim+strdust25_1;//9
      sendMessage += delim+strdust25_2;//10
      sendMessage += delim+strdust25_3;//11        
      sendMessage += delim+strdust25_3_aveSmooth;//12
      sendMessage += delim+strdust25_3_expoSmooth;//13    
      sendMessage += delim+strdust25_3_medianKalman;//14    
    }         
    Serial.println("["+sendMessage+"]");
    
    /*
    String sendMessage;  
    sendMessage = strtemp;//1
    Serial.print(sendMessage);
    sendMessage = delim+strhumi;//2
    Serial.print(sendMessage);
    sendMessage = delim+strtvoc;//3
    Serial.print(sendMessage);
    sendMessage = delim+streco2;//4
    Serial.print(sendMessage);
    sendMessage = delim+strROU;//5
    Serial.print(sendMessage);
    sendMessage = delim+strUnit;//6
    Serial.print(sendMessage);
    sendMessage = delim+strRTime;//7
    Serial.print(sendMessage);
    sendMessage = delim+strValue;//8
    Serial.print(sendMessage);
    //+ radon
    if(outMode==THREE_SMOOTH_KALMAN_MEDIAN){
      sendMessage = delim+strdust25_1;//9
      Serial.print(sendMessage);
      sendMessage = delim+strdust25_2;//10
      Serial.print(sendMessage);
      sendMessage = delim+strdust25_3;//11        
      Serial.print(sendMessage);
      sendMessage = delim+strdust25_3_aveSmooth;//12
      Serial.print(sendMessage);
      sendMessage = delim+strdust25_3_expoSmooth;//13    
      Serial.print(sendMessage);
      sendMessage = delim+strdust25_3_medianKalman;//14    
      Serial.print(sendMessage);
    }         
    Serial.print('\n');
  */
}
