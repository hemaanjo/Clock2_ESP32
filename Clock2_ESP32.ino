#include "src\OTA.H"
#include "src\config.h"
#include "src\time.h"

void setup() {
  // put your setup code here, to run once:
  ota::setup();
  Config::checkFileSystem();
  Config::load();
  Time::setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  ota::loop();
  Time::loop();
}
