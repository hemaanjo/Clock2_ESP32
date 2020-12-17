#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>

#include "utcOffset.h"
#include "config.h"

int UtcOffset::getLocalizedUtcOffset() {
  HTTPClient http;
  http.begin("http://worldtimeapi.org/api/timezone/Europe/Berlin.json");
  int responseCode = http.GET();

  if (responseCode > 0) {
    String payload = http.getString();
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return Config::timezone;
    }
    Serial.println(doc["timezone"].as<String>());

    int utcOffset = doc["raw_offset"].as<int>();
    int dstOffset = doc["dst_offset"].as<int>();

    http.end();
    return utcOffset + dstOffset;
  } else {
    Serial.println("NoResponse");
  }
  http.end();
  return Config::timezone; // return last known offset
}
