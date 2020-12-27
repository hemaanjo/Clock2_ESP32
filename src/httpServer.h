#ifndef WORDCLOCK_SERVER_H
#define WORDCLOCK_SERVER_H

#include <WebServer.h>


class HttpServer {
  public:
    static  WebServer web;
    static String ip;
    
    static void setup();
    static void loop();
};

#endif
