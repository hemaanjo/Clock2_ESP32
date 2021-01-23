#include <PubSubClient.h>

class mqtt {
    const char* mqtt_server = "192.168.1.103";

/* create an instance of PubSubClient client */
WiFiClient espClient;
PubSubClient client(espClient);

}