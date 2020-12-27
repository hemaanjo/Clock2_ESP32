#include <ArduinoJson.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
//#include <WiFiManager.h>
#include <FastLED.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FS.h>

#include "src/OTA.H"
#include "src/grid.h"
/*#include "src/wifi.h"*/
#include "src/types.h"
#include "src/color.h"
#include "src/config.h"
#include "src/dnd.h"
#include "src/led.h"
#include "src/time.h"
#include "src/httpServer.h"
#include "src/gui.h"
#include "src/controller.h"

void setup() {
  Serial.begin(115200);
  Serial.println();
  ota::setup();
  SPIFFS.begin();

  Config::load();

  /*Wifi::setup();*/
  HttpServer::setup();
  Led::setup();
  Time::setup();

  Grid::setTime(Time::hour, Time::minute);
}

void loop() {
  ota::loop();
  Time::loop();
  HttpServer::loop();
}
