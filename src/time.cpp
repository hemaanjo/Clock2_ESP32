#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "time.h"
#include "utcOffset.h"
#include "config.h"
#include "grid.h"

void Time::setup() {
  Time::ntpClient.begin();
  Time::ntpClient.setTimeOffset(0);
  Time::ntpClient.update();
}

void Time::loop() {
  Time::ntpClient.update();

  int h = Time::ntpClient.getHours();
  int m = Time::ntpClient.getMinutes();
  int s = Time::ntpClient.getSeconds();

  if(s != Time::second) {
    Time::second = s;
    //if((s%5)==0) {
    if((Config::ambilight > 0) && (s % 60 !=0)) {
      Serial.println(s);
      Grid::setSecond(Time::second);
      }
    //  }
    }

  int min4 = m;
  if(m != Time::minute) {
    Serial.println("");
    if(m == 0 && h == Time::hour) {
      h = (h + 1) % 24;
    }
    if((m % 5)==0) {
      Time::hour = h;
      Time::minute = m;
      Grid::setTime(Time::hour, Time::minute);
     //Serial.print(h);Serial.print(":");Serial.println(m);
      Serial.println(Time::ntpClient.getFormattedTime());
      
      Grid::setTime(Time::hour, Time::minute);

    } else {
      Time::minute = m;
      Grid::setSingleMinute(Time::minute);
      Serial.println((m%5));
    }
    

    //Serial.println("Config::automatic_timezone" + Config::automatic_timezone);
    if (Config::automatic_timezone) {
      Config::timezone = UtcOffset::updateLocalizedUtcOffset();
      Serial.print("per Minute AutoZone="); Serial.println(Config::timezone);
      Time::ntpClient.setTimeOffset(Config::timezone);
    }
    
  } // minute changed
}

int Time::hour = -1;
int Time::minute = -1;
int Time::second = -1;
WiFiUDP Time::udp;
NTPClient Time::ntpClient = NTPClient(Time::udp);