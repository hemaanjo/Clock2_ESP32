#ifndef OTA_H
#define OTA_H
//#include "..\user_config.h" 
#include "config.h"

class ota {
  public:
    static String ssid;
    static String password;


    static void setup();

    static void loop();
};

#endif
