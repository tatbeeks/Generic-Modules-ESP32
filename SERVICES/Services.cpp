/**
 ************************************************************************                  
 * @file                    : Services.c
 * @author                  : Ahmed Hesham
 * @brief                   : Services source file
 
 Services module represent a seperate module that handles the operation of publishing data through mqtt protocol.
 to use :
 1-call Client_Init() in your setup function
 2-before publishing, call Client_Connect() and after calling it, check the value of the variable Client_Connectivity_Flag.
 3-If value of this variable is true, then start your publishing sequence by calling Client_Publish().
 
 notes: you only need to modify strings and topic names in Client_Publish() function with no need to modify anything else.
 make sure that variables you want to publish are golobal variables defined and available to this module be means of including header files of these variables modules.
 ************************************************************************
 */

#include "Services.h"

//define object
WiFiClient espClient;
PubSubClient client(espClient);
//flag to check the server connectivity in main loop
byte Client_Connectivity_Flag;

//server info
const char* mqttServer = "35.172.244.127";  //mqtt server
const int mqttPort = 1883;                  //mqtt port
const char* mqttUser = "amr";               //mqtt username
const char* mqttPassword = "amr123";        //mqtt password

void Client_Init(void) {
  client.setServer(mqttServer, mqttPort);
}

void Client_Connect(void) {
  //connect to MQTT
  byte repeat = 0;
  //initialise the flag as true
  Client_Connectivity_Flag = 1;
  //try to connect to server twice and put the result of trials in Client_Connectivity_Flag variable
  while ((!client.connected()) && (repeat < 2)) {

    Serial.println("Connecting to MQTT...");

    if (client.connect("", mqttUser, mqttPassword)) {
      Serial.println("connected");
      Client_Connectivity_Flag = 1;
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      Client_Connectivity_Flag = 0;
    }
    repeat++;
    delay(100);
  }
}


//function used to publish the values. Should be called fter Client_Connect() function.
//to send values through mqtt protocol, they must be converted into strings. Use in-built function like itoa() or dtoa().
void Client_Publish(void) {
  char result1[3];
  char result2[3];
  char result3[3];
  char result4[8];

  itoa(Nitrogen_val, result1, 10);
  client.publish("TOPIC/NAME", result1);


  itoa(phosphorous_val, result2, 10);
  client.publish("TOPIC/NAME", result2);


  itoa(potassium_val, result3, 10);
  client.publish("TOPIC/NAME", result3);


  dtostrf(TDS_Value, 6, 2, result4);
  client.publish("TOPIC/NAME", result4);


}
