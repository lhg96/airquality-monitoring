
enum {
  cmd_RS9A_VALUE_QUERY = 0x01, // value query
  cmd_RS9A_RESET_QUERY = 0x02, // measurement process initialized
  cmd_RS9A_VERSION_QUERY = 0x03, // firmware version check
  cmd_RS9A_SN_QUERY = 0x04, // serial number check
  cmd_RS9A_UNIT_PCI_CHANGE_QUERY = 0x05, // unit : pCi/L change
  cmd_RS9A_UNIT_BQ_CHANGE_QUERY = 0x06, // unit : Bq/m3 change
};

bool request_flag = true; // enable or disable send command automatically
int sendPeriod = 5000; // "cmd_RS9A_VALUE_QUERY" request period, unit : ms

void initRS9A(){
  radonSerial.begin(19200); // Arduino - RS9A  
  delay(1000);
  CommandSend(cmd_RS9A_VERSION_QUERY);
  CommandSend(cmd_RS9A_SN_QUERY);
  //CommandSend(cmd_RS9A_UNIT_BQ_CHANGE_QUERY); //초기화시 BQ로 수치 변경
  Serial.println("RS9A Start====================================================");  
}
/**
 * parsing
 */
void readRS9A(){
  SendCmdValue();
  String str = recUartData();    
  if(str!= NULL){
    //Serial.print(str);    
    String str0 = getValue(str, ':',0);
    String str1 = getValue(str, ':',1);
    String str2 = getValue(str, ':',2);
    String str3 = getValue(str, ':',3);
    String str4 = getValue(str, ':',4);
    str0.trim();
    str1.trim();
    str2.trim();    
    str3.trim();    
    str4.trim();    
    //Serial.println(str1);
    //Serial.println(str2);
    //Serial.println(str3);    
    if(str0.equals("STATUS READY")){       
       Sensor.RS9A.rTime = parseRTime(str1);       
       Sensor.RS9A.unit = parseUnit(str2);
       //Serial.println("RTime :"+String(Sensor.RS9A.rTime));            
       //Serial.println("Unit :"+String(Sensor.RS9A.unit));
    }else if(str0.equals("STATUS NORMAL")){      
       Sensor.RS9A.value = parseValue(str1);       
       Sensor.RS9A.rou = parseROU(str2);       
       Sensor.RS9A.rTime = parseRTime(str3);       
       Sensor.RS9A.unit = parseUnit(str4);
       //Serial.println("value :"+String(Sensor.RS9A.value));         
       //Serial.println("ROU :"+String(Sensor.RS9A.rou));         
       //Serial.println("RTime :"+String(Sensor.RS9A.rTime)); 
       //Serial.println("Unit :"+String(Sensor.RS9A.unit)); 
    }else if(str0.equals("STATUS ERR1")){  
    }else if(str0.equals("STATUS ERR2")){  
    }
  }  
}

int parseUnit(String term){
  String valueHeader = getValue(term, ' ',0);
  String valueStr    = getValue(term, ' ',1);
  valueHeader.trim();
  valueStr.trim();
  return valueStr.toInt();
}
int parseRTime(String term){
  String valueHeader = getValue(term, ' ',0);
  String valueStr    = getValue(term, ' ',1);
  valueHeader.trim();
  valueStr.trim();
  return valueStr.toInt();
}
float parseValue(String term){
  String valueHeader = getValue(term, ' ',0);
  String valueStr    = getValue(term, ' ',1);
  valueHeader.trim();
  valueStr.trim();
  return valueStr.toFloat();   
}
float parseROU(String term){
  String valueHeader = getValue(term, ' ',0);
  String valueStr    = getValue(term, ' ',1);
  valueHeader.trim();
  valueStr.trim();
  return valueStr.toFloat();   
}


// https://stackoverflow.com/questions/9072320/split-string-into-string-array
String getValue(String data, char separator, int index){
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void SendCmdValue(){
  //radonSerial.write("VALUE?\r\n", 8);
  radonSerial.println("VALUE?"); //mfix
}

/* send to RS9A */
void CommandSend(int cmd){
  switch(cmd){
    case cmd_RS9A_RESET_QUERY:
    //radonSerial.write("RESET\r\n", 7);
    radonSerial.println("RESET"); //mfix
    delay(100);
    break;
    case cmd_RS9A_VERSION_QUERY:
    //radonSerial.write("VERSION?\r\n", 10);
    radonSerial.println("VERSION?"); //mfix
    delay(100);
    break;
    case cmd_RS9A_SN_QUERY:
    //radonSerial.write("SERIALNO?\r\n", 11);
    radonSerial.println("SERIALNO?"); //mfix
    delay(100);
    break;
    case cmd_RS9A_UNIT_PCI_CHANGE_QUERY:
    //radonSerial.write("UNIT 0\r\n", 8);
    radonSerial.println("UNIT 0"); //mfix
    delay(100);
    break;
    case cmd_RS9A_UNIT_BQ_CHANGE_QUERY:
    //radonSerial.write("UNIT 1\r\n", 8);
    radonSerial.println("UNIT 1"); //mfix
    delay(100);
    break;
  }
}

String recUartData(){  
  int rec_size = radonSerial.available();      
  String oneLine;
  if (rec_size > 0) {
    char rec_data[50]; // Array for received command
    memset(rec_data, 0, 50);
    for (int i = 0; i < rec_size; i++){
      rec_data[i] = radonSerial.read();
      //Serial.print(String(i)+"."); //test
      //Serial.print(rec_data[i]); 
    }      
    String recString(rec_data);
    oneLine = recString;    
  }
  return oneLine;
}
