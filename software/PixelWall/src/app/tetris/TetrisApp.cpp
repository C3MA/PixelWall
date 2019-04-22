#include "TetrisApp.h"
#include "Stones.h"
#include <stdlib.h>

TetrisApp::TetrisApp(LedPanel* panelPnt, void(*sendWebsocketDataCb)(char* payload, uint8_t len))
{
	panel = panelPnt;
	sendWebsocketData = sendWebsocketDataCb;
	loadNextStone();
}

void TetrisApp::start()
{
	showStartScreen();
}

void TetrisApp::end()
{
	gameRunning = false;
}

void TetrisApp::showStartScreen()
{
	panel->clear();
	panel->setLed(1, 3, RGBColor(255, 0, 0), 0);
	panel->setLed(2, 3, RGBColor(255, 0, 0), 0);
	panel->setLed(2, 4, RGBColor(255, 0, 0), 0);
	panel->setLed(3, 4, RGBColor(255, 0, 0), 0);

	panel->setLed(1, 4, RGBColor(0, 0, 255), 0);
	panel->setLed(1, 5, RGBColor(0, 0, 255), 0);
	panel->setLed(2, 5, RGBColor(0, 0, 255), 0);
	panel->setLed(3, 5, RGBColor(0, 0, 255), 0);

	panel->setLed(3, 3, RGBColor(255, 128, 0), 0);
	panel->setLed(4, 3, RGBColor(255, 128, 0), 0);
	panel->setLed(4, 4, RGBColor(255, 128, 0), 0);
	panel->setLed(4, 5, RGBColor(255, 128, 0), 0);

	panel->setLed(5, 3, RGBColor(255, 0, 255), 0);
	panel->setLed(5, 4, RGBColor(255, 0, 255), 0);
	panel->setLed(5, 5, RGBColor(255, 0, 255), 0);
	panel->setLed(6, 4, RGBColor(255, 0, 255), 0);

	panel->setLed(6, 3, RGBColor(255, 0, 0), 0);
	panel->setLed(7, 3, RGBColor(255, 0, 0), 0);
	panel->setLed(7, 4, RGBColor(255, 0, 0), 0);
	panel->setLed(8, 4, RGBColor(255, 0, 0), 0);

	panel->setLed(8, 3, RGBColor(0, 0, 255), 0);
	panel->setLed(9, 3, RGBColor(0, 0, 255), 0);
	panel->setLed(10, 3, RGBColor(0, 0, 255), 0);
	panel->setLed(10, 4, RGBColor(0, 0, 255), 0);

	panel->setLed(8, 5, RGBColor(255, 0, 255), 0);
	panel->setLed(9, 5, RGBColor(255, 0, 255), 0);
	panel->setLed(10, 5, RGBColor(255, 0, 255), 0);
	panel->setLed(9, 4, RGBColor(255, 0, 255), 0);

	panel->setLed(6, 5, RGBColor(255, 255, 0), 0);
	panel->setLed(7, 5, RGBColor(255, 255, 0), 0);
	panel->setLed(6, 6, RGBColor(255, 255, 0), 0);
	panel->setLed(7, 6, RGBColor(255, 255, 0), 0);

	panel->setLed(5, 6, RGBColor(0, 255, 0), 0);
	panel->setLed(5, 7, RGBColor(0, 255, 0), 0);
	panel->setLed(6, 7, RGBColor(0, 255, 0), 0);
	panel->setLed(6, 8, RGBColor(0, 255, 0), 0);

	panel->setLed(4, 6, RGBColor(0, 255, 255), 0);
	panel->setLed(4, 7, RGBColor(0, 255, 255), 0);
	panel->setLed(4, 8, RGBColor(0, 255, 255), 0);
	panel->setLed(4, 9, RGBColor(0, 255, 255), 0);

	panel->setLed(7, 7, RGBColor(0, 0, 255), 0);
	panel->setLed(7, 8, RGBColor(0, 0, 255), 0);
	panel->setLed(7, 9, RGBColor(0, 0, 255), 0);
	panel->setLed(6, 9, RGBColor(0, 0, 255), 0);

	panel->setLed(5, 8, RGBColor(255, 128, 0), 0);
	panel->setLed(5, 9, RGBColor(255, 128, 0), 0);
	panel->setLed(5, 10, RGBColor(255, 128, 0), 0);
	panel->setLed(6, 10, RGBColor(255, 128, 0), 0);

	panel->setLed(4, 10, RGBColor(0, 255, 0), 0);
	panel->setLed(4, 11, RGBColor(0, 255, 0), 0);
	panel->setLed(5, 11, RGBColor(0, 255, 0), 0);
	panel->setLed(5, 12, RGBColor(0, 255, 0), 0);

	panel->setLed(7, 10, RGBColor(255, 0, 0), 0);
	panel->setLed(7, 11, RGBColor(255, 0, 0), 0);
	panel->setLed(6, 11, RGBColor(255, 0, 0), 0);
	panel->setLed(6, 12, RGBColor(255, 0, 0), 0);

	panel->setLed(4, 12, RGBColor(255, 0, 255), 0);
	panel->setLed(4, 13, RGBColor(255, 0, 255), 0);
	panel->setLed(4, 14, RGBColor(255, 0, 255), 0);
	panel->setLed(5, 13, RGBColor(255, 0, 255), 0);

	panel->setLed(7, 12, RGBColor(0, 255, 255), 0);
	panel->setLed(7, 13, RGBColor(0, 255, 255), 0);
	panel->setLed(7, 14, RGBColor(0, 255, 255), 0);

	panel->setLed(6, 13, RGBColor(255, 255, 0), 0);
	panel->setLed(6, 14, RGBColor(255, 255, 0), 0);
	panel->setLed(5, 14, RGBColor(255, 255, 0), 0);

	panel->show();
}

void TetrisApp::startNewGame()
{
	score = 0;
	
	currSpeed = GAME_START_SPEED;
	gameSpeed = GAME_START_SPEED;
	speedCnt = 0;
	panel->clear();
	panel->show();
	loadNextStone();

	gameRunning = true;
}

void TetrisApp::moveDown()
{
	if (currStoneIsMoveable(currStoneX, currStoneY+1))
	{
		currStoneY++;
	}
	else
	{
		drawStone(currStoneX, currStoneY, &currStone, 0);
		deleteFullRows();
		loadNextStone();
		if (!currStoneIsMoveable(currStoneX, currStoneY))
		{
			gameOver();
		}
	}

	refreshDisplay = true;
}

void TetrisApp::loadNextStone()
{
	unsigned int randomIndex = random(0, 7);

	currStone.width = stones.stone[randomIndex].width;
	currStone.height = stones.stone[randomIndex].height;
	currStone.color = stones.stone[randomIndex].color;
	memcpy(currStone.imgData, stones.stone[randomIndex].imgData, 6 * (sizeof(int)));

	currStoneX = 5;
	currStoneY = 0;
	currSpeed = gameSpeed;
}

bool TetrisApp::currStoneIsMoveable(unsigned int col, unsigned int row)
{
	for (int r = 0; r < currStone.height; r++)
	{
		for (int c = 0; c < currStone.width; c++)
		{
			if (currStone.imgData[c + r * currStone.width] == 1)
			{
				if (col + c >= panel->COLS) return false;
				if (row + r >= panel->ROWS) return false;

				if (panel->isSet(col + c, row + r, 0))
					return false;
			}
		}
	}

	return true;
}

void TetrisApp::deleteFullRows()
{
	int rowsDeleted = 0;

	bool fullRow = false;
	for (unsigned int y = 0; y < panel->ROWS; y++)
	{
		fullRow = true;
		for (unsigned int x = 0; x < panel->COLS; x++)
		{
			if (!panel->isSet(x, y, 0))
				fullRow = false;
		}

		if (fullRow == true)	//last iteration detected a full row
		{
			panel->clearRowAndFall(y,0);
			rowsDeleted++;
		}
		
	}

	score += (rowsDeleted*rowsDeleted);
	refreshScore = true;
}

void TetrisApp::loop()
{
	if (gameRunning)
	{
		if(refreshDisplay)
		{
			panel->clear(1);
			drawStone(currStoneX, currStoneY, &currStone, 1);
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

void TetrisApp::newWebsocketData(uint8_t * payload, size_t lenght)
{
	if(payload[0]=='l')
	{
		if (currStoneIsMoveable(currStoneX-1, currStoneY))
		{
			currStoneX--;
			refreshDisplay = true;
		}
	}

	if(payload[0]=='r')
	{
		if (currStoneIsMoveable(currStoneX + 1, currStoneY))
		{
			currStoneX++;
			refreshDisplay = true;
		}
	}

	if (payload[0] == 't')	//turn
	{
		if (!gameRunning)
		{
			startNewGame();
			sendScore();
		}
		else
		{
			rotate();
			refreshDisplay = true;
		}
	}

	if (payload[0] == 'd')	//fast down
	{
		currSpeed = FAST_DOWN_SPEED;
		refreshDisplay = true;
	}

	if (payload[0] == 'n')	//normal down
	{
		currSpeed = gameSpeed;
	}

	if (payload[0] == 'p')	//pause
	{
		if(gameRunning)
		{
			gameRunning = false;
		}
		else
		{
			gameRunning = true;
		}
	}
}

WebsiteResponse_t TetrisApp::getWebsiteResponse(String parameter)
{
	WebsiteResponse_t response;

	response.statusCode = 200;
	response.header1 = WebSites::HTMLHeader1;
	strcpy(response.title, "Tetris");
	response.header2 = WebSites::HTMLHeader2;
	response.body = WebSites::HTMLTetris;

	return response;
}

void TetrisApp::buttonEvent(Buttons::ButtonEvent_t btnEvent)
{
	if(btnEvent.button == Buttons::Button_t::NES_START && btnEvent.event == Buttons::Event_t::DOWN)
	{
		if(!gameRunning)
		{
			startNewGame();
			sendScore();
		}
	}
	else if(btnEvent.button == Buttons::Button_t::NES_RIGHT && btnEvent.event == Buttons::Event_t::DOWN)
	{
		if (currStoneIsMoveable(currStoneX + 1, currStoneY))
		{
			currStoneX++;
			refreshDisplay = true;
		}
	}
	else if(btnEvent.button == Buttons::Button_t::NES_LEFT && btnEvent.event == Buttons::Event_t::DOWN)
	{
		if (currStoneIsMoveable(currStoneX-1, currStoneY))
		{
			currStoneX--;
			refreshDisplay = true;
		}
	}
	else if(btnEvent.button == Buttons::Button_t::NES_A && btnEvent.event == Buttons::Event_t::DOWN)
	{
		rotate();
		refreshDisplay = true;
	}
	else if((btnEvent.button == Buttons::Button_t::NES_DOWN || btnEvent.button == Buttons::Button_t::NES_B) && btnEvent.event == Buttons::Event_t::DOWN)
	{
		currSpeed = FAST_DOWN_SPEED;
		refreshDisplay = true;
	}
	else if(btnEvent.button == Buttons::Button_t::NES_DOWN && btnEvent.event == Buttons::Event_t::UP)
	{
		currSpeed = gameSpeed;
		refreshDisplay = true;
	}

}

void TetrisApp::timerTick()
{
	if (gameRunning)
	{
		speedCnt++;
		if (speedCnt >= currSpeed)
		{
			speedCnt = 0;
			moveDown();
		}
	}
}

String TetrisApp::getName()
{
    return "tetris";
}

void TetrisApp::drawStone(int col, int row, IStone* stone, unsigned int layer)
{
	for (int r = 0; r < stone->height; r++)
	{
		for (int c = 0; c < stone->width; c++)
		{
			if (stone->imgData[c + r * stone->width] == 1)
			{
				panel->setLed(col+c, row+r, stone->color, layer);
			}
		}
	}
}

void TetrisApp::rotate()
{
	
	unsigned int  newWidth = currStone.height;
	unsigned int  newHeight = currStone.width;
	unsigned int  newImgData[6];	//the largest stone has a size of 6

	unsigned int  indexNew = 0;
	unsigned int  indexCurr = 0;
	for(unsigned int x = 0; x < currStone.width; x++)
	{
		for(unsigned int y = 0; y < currStone.height; y++)
		{
			indexCurr = (currStone.height - y - 1) * currStone.width + x;
			newImgData[indexNew] = currStone.imgData[indexCurr];
			indexNew++;
		}
	}

	for(unsigned int i = 0; i < newWidth*newHeight;i++)
	{
		currStone.imgData[i] = newImgData[i];
	}
	currStone.width = newWidth;
	currStone.height = newHeight;

}

void TetrisApp::sendScore()
{
	char buffer[10];
	itoa (score,buffer,10);
	sendWebsocketData(buffer, strlen(buffer));
}

void TetrisApp::gameOver()
{
	gameRunning = false;

	panel->clear();
	panel->printImage(panel->icons.badSmileySmall, 3, 1, RGBColor(255, 0, 0), true, 0);
	panel->printNumber(score, 1, 6, RGBColor(255, 255, 255), 0);
	panel->show();

}