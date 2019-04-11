#include "SnakeApp.h"
#include <stdlib.h>

SnakeApp::SnakeApp(LedPanel* panelPnt, void(*sendWebsocketDataCb)(char* payload, uint8_t len))
{
	panel = panelPnt;
	sendWebsocketData = sendWebsocketDataCb;
}

void SnakeApp::start()
{
	showStartScreen();
}

void SnakeApp::end()
{
	gameRunning = false;
}

void SnakeApp::showStartScreen()
{
	panel->clear();
	panel->printLineH(4, 2, 7, RGBColor(0, 0, 255), 0);
	panel->printLineV(4, 2, 4, RGBColor(0, 0, 255), 0);
	panel->printLineH(4, 6, 5, RGBColor(0, 0, 255), 0);
	panel->printLineV(9, 6, 4, RGBColor(0, 0, 255), 0);
	panel->printLineH(3, 9, 7, RGBColor(0, 0, 255), 0);
	panel->setLed(3, 10, RGBColor(0, 0, 255), 0);
	panel->setLed(3, 12, RGBColor(255, 128, 0), 0);

	panel->show();
}

void SnakeApp::startNewGame()
{
	score = 0;
	gameRunning = true;
	currSpeed = GAME_START_SPEED;
	speedCnt = 0;
	panel->clear();
	panel->show();
}

void SnakeApp::loop()
{
	if (gameRunning)
	{
		if(refreshDisplay)
		{
			//panel->clear(1);
			//panel->show();
			refreshDisplay = false;
		}

		if(refreshScore)
		{
			sendScore();
			refreshScore = false;
		}
	}

}

void SnakeApp::newWebsocketData(uint8_t * payload, size_t lenght)
{
	if(payload[0]=='l')
	{

	}

	if(payload[0]=='r')
	{
		
	}

	if(payload[0]=='u')
	{
		
	}

	if (payload[0] == 'd')	//fast down
	{
		
	}
}

WebsiteResponse_t SnakeApp::getWebsiteResponse(String parameter)
{
	WebsiteResponse_t response;

	response.statusCode = 200;
	response.header1 = WebSites::HTMLHeader1;
	strcpy(response.title, "Snake");
	response.header2 = WebSites::HTMLHeader2;
	response.body = WebSites::HTMLTetris;

	return response;
}

void SnakeApp::buttonEvent()
{

}

void SnakeApp::timerTick()
{
	if (gameRunning)
	{
		speedCnt++;
		if (speedCnt >= currSpeed)
		{
			speedCnt = 0;
		}
	}
}

String SnakeApp::getName()
{
    return "snake";
}

void SnakeApp::sendScore()
{
	char buffer[10];
	itoa (score,buffer,10);
	//sendWebsocketData(buffer, strlen(buffer));
}

void SnakeApp::gameOver()
{
	gameRunning = false;

	panel->clear();
	panel->printImage(panel->icons.badSmileySmall, 3, 1, RGBColor(255, 0, 0), true, 0);
	panel->printNumber(score, 1, 6, RGBColor(255, 255, 255), 0);
	panel->show();
}