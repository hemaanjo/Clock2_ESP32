#include <WiFi.h>
#include <WiFiManager.h>

#include "wifi.h"

void myWifi::setup() {
  WiFi.hostname("WordClock");

  WiFiManager wifiManager;
  wifiManager.autoConnect("WordClock");
}

void myWifi::reset() {
  WiFi.disconnect(true);
}
