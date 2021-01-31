#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

#include "config.h"
#include "types.h"
#include "time.h"
//#include "led.h"
#include "utcOffset.h"

void Config::checkFileSystem() {
    String dirname = "/";
    uint level =0;
    //SPIFFS fs=;
    if(!SPIFFS.begin(true)){
        Serial.println("SPIFFS Mount Failed");
        bool formatted = SPIFFS.format();
        if ( formatted ) {
          Serial.println("SPIFFS formatted successfully");
          SPIFFS.begin();
        } else {
          Serial.println("Error formatting");
          return;
        }
    }
}


void Config::save() {
  File file = SPIFFS.open("/wordclock_config.json", "w");

  if(!file) {
    Serial.println("Can't open wordclock_config.json for writing");
    return;
  }

  Serial.println("Save config.");

  Time::ntpClient.setPoolServerName(Config::ntp.c_str());
  Time::ntpClient.setTimeOffset(Config::timezone);

  StaticJsonDocument<1024> doc;
  doc["color_bg_r"] = Config::color_bg.r;
  doc["color_bg_g"] = Config::color_bg.g;
  doc["color_bg_b"] = Config::color_bg.b;
  doc["color_fg_r"] = Config::color_fg.r;
  doc["color_fg_g"] = Config::color_fg.g;
  doc["color_fg_b"] = Config::color_fg.b;
  doc["power_supply"] = Config::power_supply;
  doc["brightness"] = Config::brightness;
  doc["tz_auto"] = Config::automatic_timezone;
  doc["timezone"] = Config::timezone;
  doc["dnd_active"] = Config::dnd_active;
  doc["dnd_start_hour"] = Config::dnd_start.hour;
  doc["dnd_start_minute"] = Config::dnd_start.minute;
  doc["dnd_end_hour"] = Config::dnd_end.hour;
  doc["dnd_end_minute"] = Config::dnd_end.minute;
  doc["ntp"] = Config::ntp;
  doc["plugin_name"] = Config::plugin_name;
  doc["ambi_active"] = Config::ambilight;
  //doc["ambilight_leds"] = Config::ambilight_leds;
  //doc["ambilight_startIDX"] = Config::ambilight_startIDX;
  doc["ambilight_color_r"] = Config::ambilight_color.r;
  doc["ambilight_color_g"] = Config::ambilight_color.g;
  doc["ambilight_color_b"] = Config::ambilight_color.b;
  doc["Startup_Text"] = Config::Startup_Text;
  doc["useTypeWriter"] = Config::useTypewriter;

  

  serializeJson(doc, file);

  file.close();
}


void Config::load() {
  Config::color_bg.r = 0;
  Config::color_bg.g = 0;
  Config::color_bg.b = 0;

  Config::color_fg.r = 255;
  Config::color_fg.g = 255;
  Config::color_fg.b = 255;

  Config::power_supply = 500; // default: 500mA (USB 2.0 specification)
  Config::brightness = 0.2;

  Config::automatic_timezone = true;
  Config::timezone = 0;

  Config::dnd_active = false;
  Config::dnd_start.hour = -1;
  Config::dnd_start.minute = -1;
  Config::dnd_end.hour = -1;
  Config::dnd_end.minute = -1;
  Config::ntp = NTPSERVER;

  Config::plugin_name = PLUGIN_NAME;
  Config::useTypewriter = TYPEWRITER;
  Config::ambilight = AMBILIGHT;
  Config::ambilight_color.r = 35;
  Config::ambilight_color.g = 45;
  Config::ambilight_color.b = 0;
  Config::ambilight_leds = AMBILIGHT_LED;
  Config::ambilight_startIDX = AMBILIGHT_STARTIDX;
  Config::Startup_Text = " c l o c k 2 ";
  Config::Typewriterdelay = TYPEWRITER_DELAY;

  File file = SPIFFS.open("/wordclock_config.json", "r");

  if(!file) {
    Serial.println("Failed to open config file.");
    #define FORMAT_SPIFFS_IF_FAILED true

    Config::save();
    return;
  }

  Serial.println("Load config.");

  StaticJsonDocument<1024> doc;
  deserializeJson(doc, file);

  //Serial.println(doc);

  Config::color_bg.r = doc["color_bg_r"].as<int>();
  Config::color_bg.g = doc["color_bg_g"].as<int>();
  Config::color_bg.b = doc["color_bg_b"].as<int>();

  Config::color_fg.r = doc["color_fg_r"].as<int>();
  Config::color_fg.g = doc["color_fg_g"].as<int>();
  Config::color_fg.b = doc["color_fg_b"].as<int>();

  if(doc["power_supply"]) {
    Config::power_supply = doc["power_supply"].as<int>();
  }

 // if(doc["brightness"]) {
 //   Config::brightness =
 //     (doc["brightness"].as<double>() > Led::getMaxBrightnessPercnt()) ? Led::getMaxBrightnessPercnt() : doc["brightness"].as<double>();
 // }

  if (doc["tz_auto"]) {
    Config::automatic_timezone = doc["tz_auto"].as<bool>();
  }

  if (Config::automatic_timezone) {
    Config::timezone = UtcOffset::updateLocalizedUtcOffset();
  } else {
    Config::timezone = doc["timezone"].as<int>();
  }

  Config::dnd_active = doc["dnd_active"].as<bool>();
  Config::dnd_start.hour = doc["dnd_start_hour"].as<int>();
  Config::dnd_start.minute = doc["dnd_start_minute"].as<int>();
  Config::dnd_end.hour = doc["dnd_end_hour"].as<int>();
  Config::dnd_end.minute = doc["dnd_end_minute"].as<int>();

  if(doc["ntp"]) {
    Config::ntp = doc["ntp"].as<String>();
  }

  Time::ntpClient.setPoolServerName(Config::ntp.c_str());
  Time::ntpClient.setTimeOffset(Config::timezone);

  Config::plugin_name = doc["plugin_name"].as<String>();
  Config::ambilight=doc["ambi_active"].as<int>();
  Config::ambilight_leds = doc["ambilight_leds"].as<int>();
  if(Config::ambilight != 0) {
    Config::ambilight_leds = AMBILIGHT_LED;
  }
  Config::ambilight_startIDX=doc["ambilight_startIDX"].as<int>();
  if(Config::ambilight_startIDX == 0) {
    Config::ambilight_startIDX = AMBILIGHT_STARTIDX;
  }Config::ambilight_color.r = doc["ambilight_color_r"].as<int>();
  Config::ambilight_color.g = doc["ambilight_color_g"].as<int>();
  Config::ambilight_color.b = doc["ambilight_color_b"].as<int>();
  Config::Startup_Text = doc["Startup_Text"].as<String>();
  Config::useTypewriter = doc["useTypeWriter"].as<bool>();
  if(Config::useTypewriter != TYPEWRITER) {
    Config::useTypewriter = TYPEWRITER;
  }
  if(AMBILIGHT_LED  !=0 ) {
    if(Config::ambilight_leds != AMBILIGHT_LED) {
      Config::ambilight_leds = AMBILIGHT_LED;
    }
  }
  file.close();

  Serial.print("Loaded config. ambilight_leds="); Serial.println(Config::ambilight_leds);
  Serial.print("Loaded config. useTpyWriter="); Serial.println(Config::useTypewriter);

}

color_t Config::color_bg{};
color_t Config::color_fg{};
int Config::power_supply{};
double Config::brightness{};
bool Config::automatic_timezone{};
int Config::timezone{};
bool Config::dnd_active{};
clock_time_t Config::dnd_start{};
clock_time_t Config::dnd_end{};
String Config::ntp{};
String Config::plugin_name{};
int Config::ambilight{};
int Config::ambilight_leds{};
int Config::ambilight_startIDX{};
color_t Config::ambilight_color{};
String Config::Startup_Text{};
bool Config::useTypewriter{};
int Config::Typewriterdelay{};
