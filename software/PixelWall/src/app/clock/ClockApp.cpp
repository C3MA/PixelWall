#include "ClockApp.h"

#ifdef ARDUINO
#include <ESP8266HTTPClient.h>
#endif

ClockApp::ClockApp(LedPanel* panelPnt)
{
    panel = panelPnt;
    hour = 0;
    min = 0;
    sec = 0;
    timerCnt = 0;
    refreshDisplay = true;
}

void ClockApp::start()
{
    synchTimeWithInternet();
    panel->clear();
    panel->show();
}

void ClockApp::end()
{

}

void ClockApp::loop()
{
    if(refreshDisplay)
    {
        panel->clear();
        panel->printFormatedNumber(hour, 2, 2 , 0,RGBColor(255, 255, 255), 0);
        panel->printFormatedNumber(min, 2, 2 , 6,RGBColor(255, 255, 255), 0);
        
		if (mode == 0)
		{
			panel->printFormatedNumber(sec, 2, 2, 12, RGBColor(255, 255, 255), 0);
		}
		else
		{
			panel->clearRow(14, 0);
			panel->printLineH(0, 13, 12, RGBColor(100, 100, 100), 0);
			panel->printLineH(0, 15, 12, RGBColor(100, 100, 100), 0);
			panel->setLed(0, 14, RGBColor(100, 100, 100), 0);
			panel->setLed(11, 14, RGBColor(100, 100, 100), 0);
			panel->printLineH(1, 14, sec / 6, RGBColor(0, 150, 255), 0);
		}

        panel->show();
        refreshDisplay = false;
    }
}

void ClockApp::newWebsocketData(uint8_t * payload, size_t lenght)
{
	if (payload[0] == '0')
		mode = 0;
	else
		mode = 1;

    refreshDisplay = true;
	
}

WebsiteResponse_t ClockApp::getWebsiteResponse(String parameter)
{
	WebsiteResponse_t response;

	response.statusCode = 200;
	response.header1 = WebSites::HTMLHeader1;
	strcpy(response.title, "Clock");
	response.header2 = WebSites::HTMLHeader2;
	response.body = WebSites::HTMLClock;

	return response;
}

void ClockApp::buttonEvent()
{

}

void ClockApp::timerTick()
{
    timerCnt++;
    if(timerCnt >= 100)
    {
        sec++;
        if(sec > 59) {min++; sec = 0;}
        if(min > 59) {hour++; min = 0;}
        if(hour > 23) {hour = 0;}
        timerCnt = 0;
        refreshDisplay = true;
    }
}

String ClockApp::getName()
{
    return "clock";
}

void ClockApp::synchTimeWithInternet()
{
#ifdef ARDUINO
    HTTPClient http;
    http.begin("http://worldtimeapi.org/api/timezone/Europe/Berlin.txt");
    int httpCode = http.GET();

    if (httpCode == 200) {
        String payload = http.getString(); //Get the request response payload
        Serial.println(payload);
        int beginDate = payload.indexOf("datetime") + 10;
        int beginTime = payload.indexOf('T', beginDate) + 1;
        int endTime = payload.indexOf('.', beginTime);

        String date = payload.substring(beginDate, beginTime-1);
        String time = payload.substring(beginTime, endTime);

        Serial.println("-----");
        Serial.println("Date: " + date);
        Serial.println("Time: " + time);

        hour = time.substring(0,2).toInt();
        min = time.substring(3,5).toInt();
        sec = time.substring(6,8).toInt();

    }

    http.end();
#endif
}
