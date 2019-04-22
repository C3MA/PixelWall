#ifndef CLOCK_APP_H
#define CLOCK_APP_H

#include "../IPixelApp.h"
#include "../../LedPanel.h"

class ClockApp :public IPixelApp
{
    public:
    ClockApp(LedPanel* panelPnt);
    void start();
    void end();
    void loop();
    void newWebsocketData(uint8_t * payload, size_t lenght);
	WebsiteResponse_t getWebsiteResponse(String parameter);
    void buttonEvent(Buttons::ButtonEvent_t btnEvent);
    void timerTick();
    String getName();

    private:
    LedPanel* panel;
    int hour, min, sec;
    int timerCnt;
	unsigned int mode = 0;
    bool refreshDisplay;

    void synchTimeWithInternet();
};

#endif