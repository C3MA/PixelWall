#ifndef SNAKE_APP_H
#define SNAKE_APP_H

#include "../IPixelApp.h"
#include "../../LedPanel.h"

class SnakeApp :public IPixelApp
{
    public:
	SnakeApp(LedPanel* panelPnt, void(*sendWebsocketDataCb)(char* payload, uint8_t len));
    void start();
    void end();
    void loop();
    void newWebsocketData(uint8_t * payload, size_t lenght);
	WebsiteResponse_t getWebsiteResponse(String parameter);
    void buttonEvent();
    void timerTick();
    String getName();

    private:
	void showStartScreen();
	void startNewGame();
    void sendScore();
	void gameOver();

	void(*sendWebsocketData)(char* payload, uint8_t len);

    LedPanel* panel;

	const int GAME_START_SPEED = 80;
	int currSpeed = GAME_START_SPEED;
	int speedCnt = 0;
	int score = 0;
	bool gameRunning = false;
	bool refreshDisplay = false;
	bool refreshScore = false;
};

#endif