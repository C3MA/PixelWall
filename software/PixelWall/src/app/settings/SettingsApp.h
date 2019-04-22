#ifndef SETTINGS_APP_H
#define SETTINGS_APP_H

#include "../IPixelApp.h"
#include "../../LedPanel.h"

class SettingsApp :public IPixelApp
{
    public:
	SettingsApp(LedPanel* panelPnt);
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
    char websiteBuffer[500];

};

#endif