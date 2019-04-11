#include "PixelItApp.h"
#include <stdlib.h>

PixelItApp::PixelItApp(LedPanel* panelPnt, void(*sendWebsocketDataCb)(char* payload, uint8_t len))
{
    panel = panelPnt;
}

void PixelItApp::start()
{
	panel->clear();
	panel->printImage(panel->letters.p,1,6,RGBColor(0,0,255),false,0);
	panel->printImage(panel->letters.i,4,4,RGBColor(255,0,0),false,0);
	panel->printImage(panel->letters.x,7,4,RGBColor(0,255,0),false,0);
	panel->clearLed(5, 5, 0);	//beim I ein pixel weg nehmen, damit es wie ein kleines i aussieht
	panel->show();
}

void PixelItApp::end()
{

}

void PixelItApp::loop()
{

}

void PixelItApp::newWebsocketData(uint8_t * payload, size_t length)
{
	int x, y, r, g, b;

#ifdef ARDUINO
	String str = (char *)payload;

	if (str == "c")
	{
		panel->clear();
		panel->show();
	}
	else
	{
		int begin = 0;
		int end = str.indexOf(',');
		x = str.substring(begin, end).toInt();
		begin = end + 1;
		end = str.indexOf(',', begin);
		y = str.substring(begin, end).toInt();
		begin = end + 1;
		end = str.indexOf(',', begin);
		r = str.substring(begin, end).toInt();
		begin = end + 1;
		end = str.indexOf(',', begin);
		g = str.substring(begin, end).toInt();
		begin = end + 1;
		end = str.indexOf(',', begin);
		b = str.substring(begin, end).toInt();
	}
#else
	String str = System::Text::Encoding::ASCII->GetString(payload, (int)length);
	if (str == "c")
	{
		panel->clear();
		panel->show();
	}
	else
	{
		array<String>^ strValues = str->Split(',');
		x = Int32::Parse(strValues[0]);
		y = Int32::Parse(strValues[1]);
		r = Int32::Parse(strValues[2]);
		g = Int32::Parse(strValues[3]);
		b = Int32::Parse(strValues[4]);
	}
#endif

    panel->setLed(x,y,RGBColor(r,g,b),0);
    panel->show();
}

WebsiteResponse_t PixelItApp::getWebsiteResponse(String parameter)
{
	WebsiteResponse_t response;

	response.statusCode = 200;
	response.header1 = WebSites::HTMLHeader1;
	strcpy(response.title, "PixelIt");
	response.header2 = WebSites::HTMLHeader2;
	response.body = WebSites::HTMLPixelIt;

	return response;

}

void PixelItApp::buttonEvent()
{

}

void PixelItApp::timerTick()
{
    
}

String PixelItApp::getName()
{
    return "pixelIt";
}
