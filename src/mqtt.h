#include <PubSubClient.h>

#define MQTT_server "m21.cloudmqtt.com"
#define MQTT_port 12247
#define MQTT_User "iasfjkqc"
#define MQTT_Pass "qsXY5N74m-VN"
#define MQTT_Name "Schlafzimmer"

class mqtt {
    const char* mqtt_server =  MQTT_server;

/* create an instance of PubSubClient client */
WiFiClient espClient;
PubSubClient client(espClient);
// MQTT Zugangsdaten
}