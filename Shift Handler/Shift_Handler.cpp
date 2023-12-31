/**
 ************************************************************************                  
 * @file                    : Shift_Hander.cpp
 * @author                  : Ahmed Hesham
 * @brief                   : Shift Hander Module source file

 this module handles the reset time of ESP.
 Insert this module in your code whenever you have diffrent working shifts that you need to handle staff at end of each shift (for example).
 in this example two shifts are presented (you can add more according to requirments), by the end of each shift -> data are published, counters are reset also ESP resets.
 Actions taken by end of shift are configurable.
 
 for refernce of using this module, refer to Kama Secondry ESP project 
 ************************************************************************
 */

#include "Shift_Handler.hpp"

ESP32Time rtc(10800);
//define shifts
const String shift1_h = "08";
const String shift1_m = "59";
const String shift2_h = "20";
const String shift2_m = "59";

String DD;
String HH;
String MM;
String se;

int sec;


//call this function in setup(). Make sure wifi is connected.
void Shift_Time_Init(void) {

  bool res = false;
  while (res == false) {

    String serverPath = "http://worldtimeapi.org/api/timezone/Africa/Cairo";
    HTTPClient http;
    http.begin(serverPath.c_str());
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {

      DynamicJsonDocument doc(2048);
      deserializeJson(doc, http.getStream());

      // Read values
      rtc.setTime(doc["unixtime"].as<long>());  // 1st Jan 2021 00:00:00


      res = true;
    } else {
      res = false;
      Serial.print('.');
      delay(1000);
    }
    // Free resources
    http.end();
  }
}

//call this function in loop().
void Shift_Check(void) {

  HH = rtc.getTime("%H");
  MM = rtc.getTime("%M");
  se = rtc.getTime("%S");

  sec = se.toInt();  //converts string to int

  DD = rtc.getTime("%A");

  Serial.println("time =");
  Serial.println(sec);
  Serial.println(MM);
  Serial.println(HH);
  Serial.println(DD);
  
  //this condition will be checked periodically until time is before shift end time by 3 sec.
  //make sure to perform your reset steps.
  if (((HH == shift1_h) && (MM == shift1_m) && (sec > 57)) || ((HH == shift2_h) && (MM == shift2_m) && (sec > 57))) {
      Running_time = 0;
      Down_Time = 0;
      PE_pulseCount = 0;
      Client_Publish();
      delay(3000);

      ESP.restart();
    }
}
