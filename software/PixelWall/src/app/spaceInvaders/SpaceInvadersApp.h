#ifndef SPACE_INVADERS_APP_H
#define SPACE_INVADERS_APP_H

#include "../IPixelApp.h"
#include "../../LedPanel.h"

class SpaceInvadersApp :public IPixelApp
{
    public:
	SpaceInvadersApp(LedPanel* panelPnt, void(*sendWebsocketDataCb)(char* payload, uint8_t len));
    void start();
    void end();
    void loop();
    void newWebsocketData(uint8_t * payload, size_t lenght);
	WebsiteResponse_t getWebsiteResponse(String parameter);
    void buttonEvent(Buttons::ButtonEvent_t btnEvent);
    void timerTick();
    String getName();

    private:
		static const unsigned int NUM_FIRE_BALLS = 6;
		static const unsigned int SHOOT_SPEED = 5;
		static const unsigned int NUM_ENEMIES = 162;	//(9x18)
		static const unsigned int ENEMY_SPEED = 100;

		LedPanel* panel;
		int score = 0;
		bool gameRunning = false;
		bool refreshEnemies = false;
		int enemyCnt = 0;
		int shootCnt = 0;
		unsigned int shipPos = 5;
		int fireBallX[NUM_FIRE_BALLS];
		int fireBallY[NUM_FIRE_BALLS];

		int enemyX[NUM_ENEMIES];
		int enemyY[NUM_ENEMIES];

		RGBColor colorShip = RGBColor(100, 200, 100);
		RGBColor colorEnemy = RGBColor(200, 200, 200);
		RGBColor colorFireBall = RGBColor(200, 50, 0);

		void(*sendWebsocketData)(char* payload, uint8_t len);
		
		void addNewEnemyRow();
		void showStartScreen();
		void refreshDisplay();
		void startNewGame();
		void checkForCollission(int fireBallIndex);
		void gameOver();
		void sendScore();
		void fire();

};

#endif