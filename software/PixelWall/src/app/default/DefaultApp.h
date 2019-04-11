#ifndef DEFAULT_APP_H
#define DEFAULT_APP_H

#include <Arduino.h>
#include "../IPixelApp.h"
#include "../../LedPanel.h"

class DefaultApp :public IPixelApp
{
    public:
    DefaultApp(LedPanel* panelPnt);
    void start();
    void end();
    void loop();
    void newWebsocketData(uint8_t * payload, size_t lenght);
	WebsiteResponse_t getWebsiteResponse(String parameter);
    void buttonEvent();
    void timerTick();
    String getName();

	typedef enum {
		IDLE,
		SEARCH_WLAN,
        NO_WIFI,
        SHOW_IP
	}displayMode_t;

    void setDisplayMode(displayMode_t mode);
    void setIP(int a, int b, int c, int d);

    private:
    LedPanel* panel;
	displayMode_t mode = IDLE;
    int timerCnt = 0;
    bool refreshDisplay;
    bool showIcon = true;
    int ip[4] = {0,0,0,0};
};

#endif