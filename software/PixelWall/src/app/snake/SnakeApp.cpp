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

	snakeLength = 3;
	snakeX[0] = 5;
	snakeX[1] = 5;
	snakeX[2] = 5;
	snakeY[0] = 2;
	snakeY[1] = 1;
	snakeY[2] = 0;

	snakeDir = DOWN;
	placeNewFood();

	panel->clear();
	refreshDisplay = true;
}

void SnakeApp::loop()
{
	if (gameRunning)
	{
		if(refreshDisplay)
		{
			panel->clear(0);
			for (int i = 1; i < snakeLength; i++)
			{
				panel->setLed(snakeX[i], snakeY[i], snakeColor, 0);
			}
			panel->setLed(snakeX[0], snakeY[0], headColor, 0);
			panel->setLed(foodX, foodY, foodColor, 0);
			panel->show();
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
		if(snakeDir != RIGHT)
			snakeDir = LEFT;
	}

	if(payload[0]=='r')
	{
		if (snakeDir != LEFT)
			snakeDir = RIGHT;
	}

	if(payload[0]=='u')
	{
		if (snakeDir != DOWN)
			snakeDir = UP;
	}

	if (payload[0] == 'd')
	{
		if (snakeDir != UP)
			snakeDir = DOWN;
	}

	if (payload[0] == 'p')
	{
		if (!gameRunning)
		{
			startNewGame();
		}
	}
}

WebsiteResponse_t SnakeApp::getWebsiteResponse(String parameter)
{
	WebsiteResponse_t response;

	response.statusCode = 200;
	response.header1 = WebSites::HTMLHeader1;
	strcpy(response.title, "Snake");
	response.header2 = WebSites::HTMLHeader2;
	response.body = WebSites::HTMLSnake;

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
			moveSnake();
			speedCnt = 0;
			refreshDisplay = true;
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

void SnakeApp::moveSnake()
{
	for (int i = snakeLength - 1; i > 0; i--)
	{
		snakeX[i] = snakeX[i - 1];
		snakeY[i] = snakeY[i - 1];
	}

	if (snakeDir == DOWN)
	{
		snakeY[0]++;
		if (snakeY[0] >= panel->ROWS)
			snakeY[0] = 0;
	}
	else if (snakeDir == UP)
	{
		snakeY[0]--;
		if (snakeY[0] < 0)
			snakeY[0] = panel->ROWS - 1;
	}
	else if (snakeDir == RIGHT)
	{
		snakeX[0]++;
		if (snakeX[0] >= panel->COLS)
			snakeX[0] = 0;
	}
	else if (snakeDir == LEFT)
	{
		snakeX[0]--;
		if (snakeX[0] < 0)
			snakeX[0] = panel->COLS - 1;
	}

	if (isInSnake(snakeX[0], snakeY[0], true))
		gameOver();

	if (snakeX[0] == foodX && snakeY[0] == foodY)
	{
		score++;
		if(score%3==0)
			snakeLength++;

		if (snakeLength % 3 == 0 && currSpeed > 5)
			currSpeed -= 3;

		refreshScore = true;
		placeNewFood();
	}
}

void SnakeApp::placeNewFood()
{
	do
	{ 
		foodX = random(0, panel->COLS);
		foodY = random(0, panel->ROWS);
	} while (isInSnake(foodX, foodY, false));
}

bool SnakeApp::isInSnake(int x, int y, bool ignoreHead)
{
	int start = 0;

	if (ignoreHead)
		start = 1;

	for (int i = start; i < snakeLength; i++)
	{
		if (snakeX[i] == x && snakeY[i] == y)
			return true;
	}

	return false;
}