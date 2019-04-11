#include "SpaceInvadersApp.h"
#include <stdlib.h>
#include <string.h>

SpaceInvadersApp::SpaceInvadersApp(LedPanel* panelPnt, void(*sendWebsocketDataCb)(char* payload, uint8_t len))
{
    panel = panelPnt;
	sendWebsocketData = sendWebsocketDataCb;
}

void SpaceInvadersApp::start()
{
	showStartScreen();
}

void SpaceInvadersApp::end()
{

}

void SpaceInvadersApp::loop()
{
	if (gameRunning == true)
	{
		refreshDisplay();
	}
}

void SpaceInvadersApp::refreshDisplay()
{
	panel->clear(0);

	//draw ship:
	panel->setLed(shipPos, 17, colorShip, 0);

	//draw fire balls:
	for (int i = 0; i < NUM_FIRE_BALLS; i++)
	{
		panel->setLed(fireBallX[i], fireBallY[i], colorFireBall, 0);
	}

	if (refreshEnemies)
	{
		panel->clear(1);
		for (int i = 0; i < NUM_ENEMIES; i++)
		{
			if(enemyY[i]!=-1)
				panel->setLed(enemyX[i], enemyY[i], colorEnemy, 1);
		}

		refreshEnemies = false;
	}

	panel->show();
}

void SpaceInvadersApp::newWebsocketData(uint8_t * payload, size_t length)
{
	if (payload[0] == 'l')
	{
		if (shipPos > 0)
			shipPos--;
	}

	if (payload[0] == 'r')
	{
		if (shipPos < panel->COLS-1)
			shipPos++;
	}

	if (payload[0] == 'm')
	{
#ifdef ARDUINO
		String str = (char *)payload;
		int tmpPos = str.substring(1).toInt();
#else
		String str = System::Text::Encoding::ASCII->GetString(payload, (int)length);
		int tmpPos = Int32::Parse(str->Substring(1));
#endif
		if (tmpPos >= 0 && tmpPos < panel->COLS)
			shipPos = tmpPos;
	}

	if (payload[0] == 'f')	//fire!
	{
		//search a free fire Ball:
		for (int i = 0; i < NUM_FIRE_BALLS; i++)
		{
			if (fireBallY[i] < 0)
			{
				fireBallY[i] = 16;
				fireBallX[i] = shipPos;
				break;
			}
		}
	}

	if(payload[0] == 'x')
	{
		if (gameRunning == false)
		{
			startNewGame();
		}
	}
}

WebsiteResponse_t SpaceInvadersApp::getWebsiteResponse(String parameter)
{
	WebsiteResponse_t response;
	
	response.statusCode = 200;
	response.header1 = WebSites::HTMLHeader1;
	strcpy(response.title, "Space Invaders");
	response.header2 = WebSites::HTMLHeader2;
	response.body = WebSites::HTMLSpaceInvaders;

	return response;

}

void SpaceInvadersApp::buttonEvent()
{

}

void SpaceInvadersApp::timerTick()
{
	if (gameRunning == true)
	{
		shootCnt++;
		enemyCnt++;

		if (enemyCnt >= ENEMY_SPEED)
		{
			enemyCnt = 0;
			for (int i = 0; i < NUM_ENEMIES; i++)
			{
				if (enemyY[i] >= 0)
				{
					enemyY[i]++;
					if (enemyY[i] > 15)
					{
						//game over!
						gameOver();
						return;
					}
				}
			}

			addNewEnemyRow();

			refreshEnemies = true;
		}

		if (shootCnt >= SHOOT_SPEED)
		{
			shootCnt = 0;
			for (int i = 0; i < NUM_FIRE_BALLS; i++)
			{
				if (fireBallY[i] >= 0)
				{
					fireBallY[i]--;

					checkForCollission(i);
				}
			}
		}

	}
}

String SpaceInvadersApp::getName()
{
    return "spaceInvaders";
}

void SpaceInvadersApp::addNewEnemyRow()
{
	int numOfNewEnemies = random(1, 6);
	int xPos[5] = {-1,-1,-1,-1,-1};
	int randomNumber;
	bool exists = false;

	//create random X-Positions:
	for(int i = 0; i < numOfNewEnemies; i++)
	{
		do
		{
			randomNumber = random(0, 12);

			exists = false;
			for(int j = 0; j < numOfNewEnemies; j++)
			{
				if(xPos[j] == randomNumber)
				{
					exists = true;
					break;
				}
			}
		}while(exists);

		xPos[i] = randomNumber;
	}

	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		if(enemyY[i] == -1)	//this one is free
		{
			enemyY[i] = 0;
			enemyX[i] = xPos[numOfNewEnemies-1];
			numOfNewEnemies--;
			if(numOfNewEnemies == 0 )
				break;
		}
	}
}


void SpaceInvadersApp::showStartScreen()
{
	panel->clear();
	
	panel->setLed(8,17,colorShip, 0);

	panel->setLed(8,15,colorFireBall, 0);
	panel->setLed(7,13,colorFireBall, 0);
	panel->setLed(7,11,colorFireBall, 0);
	panel->setLed(5,8,colorFireBall, 0);
	
	panel->setLed(10,2,colorEnemy, 0);
	panel->setLed(8,2,colorEnemy, 0);
	panel->setLed(2,1,colorEnemy, 0);
	panel->setLed(9,1,colorEnemy, 0);
	panel->setLed(3,1,colorEnemy, 0);
	panel->setLed(7,0,colorEnemy, 0);
	panel->setLed(6,0,colorEnemy, 0);
	panel->setLed(4,0,colorEnemy, 0);

	panel->show();
}

void SpaceInvadersApp::startNewGame()
{
	score = 0;
	gameRunning = true;
	enemyCnt = 0;
	for (int i = 0; i < NUM_FIRE_BALLS; i++)
	{
		fireBallY[i] = -1;
	}
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		enemyY[i] = -1;
	}

	panel->clear();
	panel->show();
}

void SpaceInvadersApp::checkForCollission(int fireBallIndex)
{
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		if (enemyY[i] != -1)
		{
			if (fireBallX[fireBallIndex] == enemyX[i] && fireBallY[fireBallIndex] == enemyY[i])
			{
				//treffer!
				fireBallY[fireBallIndex] = -1;
				enemyY[i] = -1;
				score++;
				refreshEnemies = true;
			}
		}
	}
}

void SpaceInvadersApp::gameOver()
{
	gameRunning = false;
	panel->clear();
	panel->printNumber(score, 1, 5, RGBColor(255, 255, 255), 0);
	panel->show();
}

void SpaceInvadersApp::sendScore()
{
	char buffer[10];
	itoa(score, buffer, 10);
	sendWebsocketData(buffer, strlen(buffer));
}