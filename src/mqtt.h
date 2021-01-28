#ifndef WORDCLOCK_MQTT_H
#define WORDCLOCK_MQTT_H


#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>


// MQTT Zugangsdaten
#define MQTT_server "openhab2.dama40.net"
#define MQTT_port 1833
#define MQTT_User "openhab2"
#define MQTT_Pass "Ehl95W23"
#define MQTT_Name "Clock2"

class WC_Mqtt {
  public:
    static String server;
    static int port;
    static String user;
    static String password;

    static void setup();
    static void loop();
    static bool reConnect();
};

#endif