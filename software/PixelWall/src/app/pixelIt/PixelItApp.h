#ifndef PIXEL_IT_APP_H
#define PIXEL_IT_APP_H

#include "../IPixelApp.h"
#include "../../LedPanel.h"

class PixelItApp :public IPixelApp
{
    public:
    PixelItApp(LedPanel* panelPnt, void(*sendWebsocketDataCb)(char* payload, uint8_t len));
    void start();
    void end();
    void loop();
    void newWebsocketData(uint8_t * payload, size_t length);
	WebsiteResponse_t getWebsiteResponse(String parameter);
    void buttonEvent(Buttons::ButtonEvent_t btnEvent);
    void timerTick();
    String getName();

    private:
    LedPanel* panel;
	void(*sendWebsocketData)(char* payload, uint8_t len);

};

#endif