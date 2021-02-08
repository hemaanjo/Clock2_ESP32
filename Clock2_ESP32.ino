#include "src/OTA.H"
#include "src/grid.h"
#include "src/types.h"
#include "src/color.h"
#include "src/config.h"
#include "src/dnd.h"
#include "src/led.h"
#include "src/time.h"
#include "src/httpServer.h"
#include "src/gui.h"
#include "src/controller.h"
#include "src/mqtt.h"
//#include "src/restapi.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  ota::setup();
  WC_Mqtt::setup();
  Config::checkFileSystem();
  Config::load();
  HttpServer::setup();
  //RestAPI::setup();
  Led::setup();
  Led::firstRun();
  Time::setup();
  Grid::setTime(Time::hour, Time::minute);
  Led::showAmbilight();
}

void loop() {
  // put your main code here, to run repeatedly:
  ota::loop();
  Time::loop();
  HttpServer::loop();
  //RestAPI::loop();
  if ((Time::second % 5) == 0) {
    WC_Mqtt::loop();
  }
}
