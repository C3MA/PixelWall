#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include "webSites.h"

class WebServer
{
  public:
    WebServer(void (*webSocketCb)(uint8_t num, WStype_t type, uint8_t *payload, size_t length),WebsiteResponse_t (*webRequestCb)(String page, String parameter));
    void start();
    void sendData(char * payload, uint8_t length);
    void loop();

  private:
    void (*wsCallback)(uint8_t num, WStype_t type, uint8_t *payload, size_t length);
    WebsiteResponse_t (*wrCallback)(String page, String parameter);
    WebSocketsServer webSocket;
    WiFiServer server;
    WebSites webSites;
};

#endif