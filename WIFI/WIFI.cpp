/**
 ************************************************************************                  
 * @file                    : WIFI.c
 * @author                  : Ahmed Hesham
 * @brief                   : WIFI Module source file

 first time you connect to a Network (in case no previous known networks around), ESP32 works as an access point (("ConfigPortal", "12345678")))
 log in to this network through your phone or laptop wifi then configure the esp to access the place network(only insert SSID&Password and left the rest fields empty) 
 then reset the esp. Now esp is ready to go live with no required anyfurther setting. this configuration is done for a particular network once for all.
 
 in case you need to reset the whole saved setting of ESP wifi .. go through Examples-> WifiManager-> Basic and make sure to uncomment line 16-> wm.resetSettings(); then upload the code.
 for more info visit the repo "https://github.com/tzapu/WiFiManager"
 ************************************************************************
 */

#include "WIFI.h"

WiFiManager wm;         // Declare wifemanager oject
String HOST = "";       // Declare HOST global string variable
String PORT = "";       // Declare PORT global string variable
String USER_NAME = "";  // Declare USER_NAME global string variable
String PASSWORD = "";   // Declare PASSWORD global string variable

int wifi_counter = 0;  // Declare wifi_counter global int variable to trace

byte WIFI_Connectivity_Flag;

void WIFI_Init(void) {
  Serial.println("Setup started......");
  /*Construct 3 objects of  wifimanager  parameter class (String ID,String label,String default value, int length) */
  WiFiManagerParameter host_("host", "host", "", 40);
  WiFiManagerParameter port_("port", "port", "", 40);
  WiFiManagerParameter userName_("userName", "userName", "", 40);
  WiFiManagerParameter password_("password", "Password", "", 40);

  /*Add parameters to configuration portal*/
  wm.addParameter(&host_);
  wm.addParameter(&port_);
  wm.addParameter(&userName_);
  wm.addParameter(&password_);
  WiFi.mode(WIFI_STA);  // Assign wifi mode to be station mode
  wm.setTimeout(120);   // If wifi is not connected and no config done within (timeout seconds) the portal will be closed
  /*Start configuration portal*/
  if (!wm.autoConnect("ConfigPortal", "12345678")) {
    Serial.println("Failed to configure");
    ESP.restart();
  }
  /*Recieve values from the configuration portal */
  HOST = host_.getValue();
  PORT = port_.getValue();
  USER_NAME = userName_.getValue();
  PASSWORD = password_.getValue();
}


//Try to Reconnect Once. call this function once you want to publish (or use wifi) as this function consume time
bool WIFI_Check(void) {

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("connected ");
    Serial.println(WiFi.localIP());  // print ESP32 IP
    delay(1000);
    return true;
  } else {
    return false;
  }
}
