
// https://dronebotworkshop.com/real-time-clock-arduino/
// https://www.pjrc.com/teensy/td_libs_DS1307RTC.html
// https://m.blog.naver.com/PostView.nhn?blogId=netcast2050&logNo=220837044552&proxyReferer=https%3A%2F%2Fwww.google.com%2F


char daysOfWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday","Thursday", "Friday", "Saturday"};

void initRTC(){
  //if(TIME_SETTING != '1')
  //RTC.adjust(DateTime(__DATE__, __TIME__));
  if (! RTC.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  //RTC.adjust(DateTime(__DATE__, __TIME__));
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(__DATE__, __TIME__));
    //RTC.adjust(DateTime(2019, 11, 05, 12, 00, 00));
  } 
}

void readTime(){
  printTime();
}

void printTime(){
  if(deb){
    DateTime now = RTC.now(); 
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  }
}
