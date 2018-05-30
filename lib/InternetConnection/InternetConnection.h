#ifndef __InternetConnection_H
#define __InternetConnection_H

#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <SoilMoisture.h>

class InternetConnection
{
public:
  bool initialize(void);
  bool initializeBlynk(void);
  void runBlynk(void);
  bool sendSoilMoistureToBlynk(SoilMoistureStatus);
  void initializeOTA(void);
  void handleOTA(void);
};

#endif