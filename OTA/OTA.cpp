/**
 ************************************************************************                  
 * @file                    : OTA.c
 * @author                  : Ahmed Hesham
 * @brief                   : OTA Module source file
 
 visit https://otadrive.com/ for more info.
 following the instructions in the provided site will give your project a particular info for your ESP32. Assign these values in OTADRIVE.setInfo(), then call OTA_Runnable()
 in your main loop. 
 ************************************************************************
 */

 #include "OTA.h"

 void OTA_Init (void)
 {
   OTADRIVE.setInfo("xxxxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxx", "v@1.0.0"); //create a new device on the website for your project then 
 }

void OTA_Runnable(void) {
  if (OTADRIVE.timeTick(CHECK_UPDATE_TIME_INTERVAL)) {
    OTADRIVE.updateFirmware();
  }
}
