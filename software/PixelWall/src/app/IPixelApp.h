#ifndef I_PIXEL_APP
#define I_PIXEL_APP

#include <Arduino.h>
#include "../web/webSites.h"

class IPixelApp
{
    public:
    virtual void start() = 0;
    virtual void end() = 0;
    virtual void loop() = 0;
    virtual void newWebsocketData(uint8_t * payload, size_t lenght) = 0;
    virtual WebsiteResponse_t getWebsiteResponse(String parameter) = 0;
    virtual void buttonEvent() = 0;

    /*  is called each 10ms
     *  do not do any blocking things! The funktion should return as soon as possible
     *  do not send Websocket Data! */
    virtual void timerTick() = 0;
    virtual String getName() = 0;
};

#endif