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



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  ota::setup();
  Config::checkFileSystem();
  Config::load();
  HttpServer::setup();
  Led::setup();
  Led::firstRun();
  Time::setup();
  
  Grid::setTime(Time::hour, Time::minute);
}

void loop() {
  // put your main code here, to run repeatedly:
  ota::loop();
  Time::loop();
  HttpServer::loop();
}
