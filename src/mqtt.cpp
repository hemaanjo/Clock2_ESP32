#include "mqtt.h"
#include "httpServer.h"

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

//WiFiClient client = server.available();
//if (client) {

PubSubClient mqtt(wclient);

void WC_Mqtt::setup() {
     // ---------------------- MQTT ---------------------------------------------------
  ///wclient = HttpServer::web.available();  
  IPAddress mqtt_server_ip;
  WiFi.hostByName(MQTT_server, mqtt_server_ip);
  Serial.println("MQTTGATEWAY:");
  Serial.println(MQTT_server);
  Serial.println(mqtt_server_ip);
  
  mqtt.setServer(MQTT_server, MQTT_port); // MQTT Port einstellen
  mqtt.setCallback(WC_Mqtt::callback);

  if (mqtt.connect(MQTT_Name,MQTT_User, MQTT_Pass)) {
    Serial.println("Mit MQTT verbunden");
    mqtt.publish("home", MQTT_Name,0);
    //.set_qos(QoS)); // im Topic hallo Präsenzmelder Name schreiben
  } 
  else {
    Serial.println("Mqtt connect Failed ;-( ");
  }
}

void WC_Mqtt::loop() {
  WC_Mqtt::reConnect();
  mqtt.loop();
}

void WC_Mqtt::callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
/*
  if ((char)payload[0] == '1') {
    digitalWrite(LED_BUILTIN , LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(LED_BUILTIN , HIGH);  // Turn the LED off by making the voltage HIGH
  }
*/
}


bool WC_Mqtt::reConnect() {
  bool connectState;
  connectState = false;
  // reconnected if not connected
  if (!mqtt.connected()) {
    //Serial.println("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = MQTT_Name;
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (mqtt.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqtt.publish("outTopic", "hello world");
      // ... and resubscribe
      mqtt.subscribe("inTopic");
      connectState = true;
    } else {
      //Serial.print("failed, rc=");
      //Serial.println(mqtt.state());
      //Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      //delay(5000);
    }
  } else {
    connectState = true;
  }
  return connectState;
}

String WC_Mqtt::server{};
int WC_Mqtt::port{};
String WC_Mqtt::password{};
String WC_Mqtt::user{};
