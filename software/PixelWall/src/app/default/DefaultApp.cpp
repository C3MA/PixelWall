#include "DefaultApp.h"

DefaultApp::DefaultApp(LedPanel* panelPnt)
{
    panel = panelPnt;
}

void DefaultApp::start()
{
	panel->clear();
    panel->show();
}

void DefaultApp::end()
{

}


void DefaultApp::loop()
{
    if(refreshDisplay)
    {
        refreshDisplay = false;
        if(mode == displayMode_t::SEARCH_WLAN)
        {
            if(showIcon)
            {
                panel->printImage(panel->icons.wlan, 3, 3,RGBColor(0,0,255), false,0);
				panel->show();
            }
            else
            {
                panel->clear();
                panel->show();
            }
        }

        if(mode == displayMode_t::NO_WIFI)
        {
            panel->printImage(panel->icons.wlan, 3, 3,RGBColor(0,0,255), true,0);
            panel->setLed(3, 8, RGBColor(255,0,0),0);
            panel->setLed(4, 7, RGBColor(255,0,0),0);
            panel->setLed(5, 6, RGBColor(255,0,0),0);
            panel->setLed(6, 5, RGBColor(255,0,0),0);
            panel->setLed(7, 4, RGBColor(255,0,0),0);
            panel->setLed(8, 3, RGBColor(255,0,0),0);
            panel->setLed(9, 2, RGBColor(255,0,0),0);

            panel->setLed(2, 12, RGBColor(255,255,255),0);
            panel->setLed(3, 12, RGBColor(255,255,255),0);
            panel->setLed(4, 12, RGBColor(255,255,255),0);
            panel->setLed(2, 13, RGBColor(255,255,255),0);
            panel->setLed(4, 13, RGBColor(255,255,255),0);
            panel->setLed(2, 14, RGBColor(255,255,255),0);
            panel->setLed(3, 14, RGBColor(255,255,255),0);
            panel->setLed(4, 14, RGBColor(255,255,255),0);
            panel->setLed(2, 15, RGBColor(255,255,255),0);
            panel->setLed(4, 15, RGBColor(255,255,255),0);
            panel->setLed(2, 16, RGBColor(255,255,255),0);
            panel->setLed(4, 16, RGBColor(255,255,255),0);

            panel->setLed(7, 12, RGBColor(255,255,255),0);
            panel->setLed(8, 12, RGBColor(255,255,255),0);
            panel->setLed(9, 12, RGBColor(255,255,255),0);
            panel->setLed(7, 13, RGBColor(255,255,255),0);
            panel->setLed(9, 13, RGBColor(255,255,255),0);
            panel->setLed(7, 14, RGBColor(255,255,255),0);
            panel->setLed(8, 14, RGBColor(255,255,255),0);
            panel->setLed(9, 14, RGBColor(255,255,255),0);
            panel->setLed(7, 15, RGBColor(255,255,255),0);
            panel->setLed(7, 16, RGBColor(255,255,255),0);
            panel->show();
        }

        if(mode == displayMode_t::SHOW_IP)
        {
            if(!showIcon)
            {
                panel->clear();
                panel->printNumber(ip[0],1,2,RGBColor(255,255,255),0);
                panel->printNumber(ip[1],1,8,RGBColor(255,255,255),0);
				panel->show();
            }
            else
            {
                panel->clear();
                panel->printNumber(ip[2],1,2,RGBColor(255,255,255),0);
                panel->printNumber(ip[3],1,8,RGBColor(255,255,255),0);
				panel->show();
            }
        }
    }
}

void DefaultApp::newWebsocketData(uint8_t * payload, size_t lenght)
{

}

WebsiteResponse_t DefaultApp::getWebsiteResponse(String parameter)
{
	WebsiteResponse_t response;

	response.statusCode = 200;
	response.header1 = WebSites::HTMLHeader1NoWs;
	strcpy(response.title, "Pixel Wall");
	response.header2 = WebSites::HTMLHeader2NoWs;
	response.body = WebSites::HTMLDefault;

	return response;
}

void DefaultApp::buttonEvent()
{

}

void DefaultApp::timerTick()
{
    timerCnt++;
    if(mode == displayMode_t::SEARCH_WLAN || mode == displayMode_t::NO_WIFI)
    {
        if(timerCnt >= 50)
        {
			showIcon = !showIcon;
            refreshDisplay = true;
            timerCnt = 0;
            loop();     //in this mode the loop is not called from main Application, so we have to do this here.
        }
    }

    if(mode == displayMode_t::SHOW_IP)
    {
        if(timerCnt >= 200)
        {
			showIcon = !showIcon;
            refreshDisplay = true;
            timerCnt = 0;
        }
    }
}

String DefaultApp::getName()
{
    return "";
}

void DefaultApp::setDisplayMode(displayMode_t mode)
{
    this->mode = mode;
    panel->clear();
    panel->show();
}

void DefaultApp::setIP(int a, int b, int c, int d)
{
    ip[0] = a;
    ip[1] = b;
    ip[2] = c;
    ip[3] = d;
}
