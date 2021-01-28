#include "mqtt.h"

// --------------- MQTT Variablen ---------------------------------------
//#ifdef ESP32
  #include <WiFi.h>
  #include <ArduinoOTA.h>
  #include <WiFiUdp.h>
  WiFiClient wclient;
//  #ifdef MDNS_SD
//    #include <ESPmDNS.h>
//  #endif
//#endif

PubSubClient mqtt(wclient);

void WC_Mqtt::setup() {
     // ---------------------- MQTT ---------------------------------------------------
  mqtt.setServer(MQTT_server, MQTT_port); // MQTT Port einstellen
  if (mqtt.connect(MQTT_Name,MQTT_User, MQTT_Pass)) {
    Serial.println("Mit MQTT verbunden");
    mqtt.publish("home", MQTT_Name,0);
    //.set_qos(QoS)); // im Topic hallo Präsenzmelder Name schreiben
  } 
  else {
    Serial.println("Mqtt connect Failed ;-( ");
  }
}

String WC_Mqtt::server{};
int WC_Mqtt::port{};
String WC_Mqtt::password{};
String WC_Mqtt::user{};
