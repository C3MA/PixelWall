#ifndef IMAGES_APP_H
#define IMAGES_APP_H

#include "../IPixelApp.h"
#include "../../LedPanel.h"

class ImagesApp :public IPixelApp
{
public:
	ImagesApp(LedPanel* panelPnt);
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
	Icons icons;
	bool refreshDisplay = true;
	int layer0Mode = 0;
	int speedLayer0Change = 3;
	int layer0TimerCnt = 0;
	int colorStep[216];
	RGBColor layer0[216];
	RGBColor staticColor[7];
	RGBColor staticGivenColor;
	RGBColor currentStaticColor;
	int staticColorStep = 0;
	bool newMode = false;

	void layer0Next();
	void getNextRainbowColor(RGBColor* srcColor, int* colorStep, int stepWidth);
	void initMode0(bool rainbow);
	void showRandom();
};

#endif