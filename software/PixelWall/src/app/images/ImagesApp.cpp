#include "ImagesApp.h"
#include <string.h>

ImagesApp::ImagesApp(LedPanel *panelPnt)
{
    panel = panelPnt;
	staticColor[0] = {0,0,255};
	staticColor[1] = {0,255,0};
	staticColor[2] = {255,0,0};
	staticColor[3] = {0,255,255};
	staticColor[4] = {255,255,0};
	staticColor[5] = {255,0,255};	
	staticColor[6] = {255,255,255};	
	currentStaticColor = {0,0,0};
}

void ImagesApp::start()
{
	for (int i = 0; i < 216; i++)
	{
		colorStep[i] = 0;
	}

	RGBColor tmpColor;
	int tmpColorStep = 0;
	for (int i = 0; i < 216; i++)
	{
		getNextRainbowColor(&tmpColor, &tmpColorStep, 2);
		layer0[i].r = tmpColor.r;
		layer0[i].g = tmpColor.g;
		layer0[i].b = tmpColor.b;
	}
}

void ImagesApp::end()
{
}

void ImagesApp::loop()
{
	if (newMode == true)
	{
		if(layer0Mode == 0)
			initMode0(true);
		else if (layer0Mode == 1)
			initMode0(false);
		else if (layer0Mode == 2)
		{
			staticColorStep++;
			if(staticColorStep > 6) staticColorStep = 0;
			staticGivenColor.r = staticColor[staticColorStep].r;
			staticGivenColor.g = staticColor[staticColorStep].g;
			staticGivenColor.b = staticColor[staticColorStep].b;
		}
		else if (layer0Mode == 3)
		{
			showRandom();
		}
		newMode = false;
	}

	if (refreshDisplay)
	{
		if(layer0Mode == 0 || layer0Mode == 1)
		{
			for (int y = 0; y < 18; y++)
			{
				for (int x = 0; x < 12; x++)
				{
					panel->setLed(x, y, layer0[y*12 + x], 0);
				}
				
			}
			panel->show();
		}

		if(layer0Mode == 2)
		{
			int stepWidth = 15;

			if(currentStaticColor.r > staticGivenColor.r + stepWidth)
				currentStaticColor.r-=stepWidth;

			if(currentStaticColor.r + stepWidth < staticGivenColor.r)
				currentStaticColor.r+=stepWidth;

			if(currentStaticColor.g > staticGivenColor.g + stepWidth)
				currentStaticColor.g-=stepWidth;

			if(currentStaticColor.g + stepWidth < staticGivenColor.g)
				currentStaticColor.g+=stepWidth;

			if(currentStaticColor.b > staticGivenColor.b + stepWidth)
				currentStaticColor.b-=stepWidth;

			if(currentStaticColor.b + stepWidth < staticGivenColor.b)
				currentStaticColor.b+=stepWidth;

			panel->setAll(currentStaticColor, 0);
			panel->show();
		}

		refreshDisplay = false;

	}
}

void ImagesApp::newWebsocketData(uint8_t *payload, size_t lenght)
{
	if (strcmp((char*)payload, "m0") == 0)
	{
		layer0Mode = 0;
		newMode = true;
	}
	if (strcmp((char*)payload, "m1") == 0)
	{
		layer0Mode = 1;
		newMode = true;
	}
	if (strcmp((char*)payload, "m2") == 0)
	{
		layer0Mode = 2;
		newMode = true;
	}
	if (strcmp((char*)payload, "m3") == 0)
	{
		layer0Mode = 3;
		newMode = true;
	}

	if (strcmp((char*)payload, "nx") == 0)
	{
		newMode = true;
	}

	if (strcmp((char*)payload, "s1") == 0)
	{
		speedLayer0Change = 5;
	}

	if (strcmp((char*)payload, "s2") == 0)
	{
		speedLayer0Change = 3;
	}

	if (strcmp((char*)payload, "s3") == 0)
	{
		speedLayer0Change = 0;
	}
}

WebsiteResponse_t ImagesApp::getWebsiteResponse(String parameter)
{
    WebsiteResponse_t response;

	response.statusCode = 200;
	response.header1 = WebSites::HTMLHeader1;
	strcpy(response.title, "Pixel Images");
	response.header2 = WebSites::HTMLHeader2;
	response.body = WebSites::HTMLImages;

	return response;
}

void ImagesApp::buttonEvent(Buttons::ButtonEvent_t btnEvent)
{
	if(btnEvent.event != Buttons::Event_t::DOWN)
		return;

	//mode Umschaltung
	if(btnEvent.button == Buttons::Button_t::APP_DOWN
	|| btnEvent.button == Buttons::Button_t::NES_LEFT
	|| btnEvent.button == Buttons::Button_t::NES_RIGHT)
    {
		if(layer0Mode < 3)
			layer0Mode++;
		else
			layer0Mode = 0;
		
		newMode = true;
    }
	//speed Umschaltung
	else if(btnEvent.button == Buttons::Button_t::APP_UP
	|| btnEvent.button == Buttons::Button_t::NES_DOWN)
    {
		if(speedLayer0Change < 6)
			speedLayer0Change++;
		else
			speedLayer0Change = 0;
    }
	else if(btnEvent.button == Buttons::Button_t::NES_UP)
    {
		if(speedLayer0Change > 0)
			speedLayer0Change--;
		else
			speedLayer0Change = 5;
    }
	if(btnEvent.button == Buttons::Button_t::NES_A
	|| btnEvent.button == Buttons::Button_t::NES_B)
    {
		newMode = true;
    }
}

void ImagesApp::timerTick()
{
	if (newMode == true)	//first change to the new mode before do anything
		return;

	layer0TimerCnt++;
	if (layer0Mode == 0 || layer0Mode == 1)
	{
		if (layer0TimerCnt >= speedLayer0Change)
		{
			layer0Next();
			layer0TimerCnt = 0;
			refreshDisplay = true;
		}
	}
	if (layer0Mode == 2)
	{
		if (layer0TimerCnt >= 2)
		{
			refreshDisplay = true;
			layer0TimerCnt = 0;
		}
	}
}

void ImagesApp::layer0Next()
{
	for (int i = 0; i < 216; i++)
	{
		getNextRainbowColor(&layer0[i], &colorStep[i], 1);
	}
}

void ImagesApp::getNextRainbowColor(RGBColor* oldColor, int* colorStep, int stepWidth)
{
	if (*colorStep == 0)	//red to high
	{
		oldColor->r += stepWidth;
		if (oldColor->r > 255)
		{
			oldColor->r = 255;
			*colorStep = 1;
		}
	}
	else if (*colorStep == 1)	//blue to low
	{
		if (oldColor->b > stepWidth)
			oldColor->b -= stepWidth;
		else
		{
			oldColor->b = 0;
			*colorStep = 2;
		}
	}
	else if (*colorStep == 2)	//green to high
	{
		oldColor->g += stepWidth;
		if (oldColor->g > 255)
		{
			oldColor->g = 255;
			*colorStep = 3;
		}
	}
	else if (*colorStep == 3)	//red to low
	{
		if(oldColor->r > stepWidth)
			oldColor->r -= stepWidth;
		else
		{
			oldColor->r = 0;
			*colorStep = 4;
		}
	}
	else if (*colorStep == 4)	//blue to high
	{
		oldColor->b += stepWidth;
		if (oldColor->b > 255)
		{
			oldColor->b = 255;
			*colorStep = 5;
		}
	}
	else if (*colorStep == 5)	//green to low
	{
		if (oldColor->g > stepWidth)
			oldColor->g -= stepWidth;
		else
		{
			oldColor->g = 0;
			*colorStep = 0;
		}
	}
}

String ImagesApp::getName()
{
    return "images";
}

void ImagesApp::initMode0(bool rainbow)
{
	RGBColor tmpColor = {0,0,0};
	int tmpColorStep = 0;
	for (int i = 0; i < 216; i++)
	{
		if (rainbow)
		{
			getNextRainbowColor(&tmpColor, &tmpColorStep, 2);
		}

		colorStep[i] = tmpColorStep;
		layer0[i].r = tmpColor.r;
		layer0[i].g = tmpColor.g;
		layer0[i].b = tmpColor.b;
	}
}

void ImagesApp::showRandom()
{
	int r, g, b;

	for (int y = 0; y < 18; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			r = random(0, 256);
			g = random(0, 256);
			b = random(0, 256);

			panel->setLed(x, y, RGBColor(r,g,b), 0);
		}

	}
	
	panel->show();
}
