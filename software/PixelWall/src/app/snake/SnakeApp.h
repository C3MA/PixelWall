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
    void buttonEvent(Buttons::ButtonEvent_t btnEvent);
    void timerTick();
    String getName();

    private:
	void showStartScreen();
	void startNewGame();
    void sendScore();
	void gameOver();

	void(*sendWebsocketData)(char* payload, uint8_t len);


private:
    LedPanel* panel;

	typedef enum {
		UP,
		LEFT,
		DOWN,
		RIGHT
	}Dir_t;

	const int GAME_START_SPEED = 60;
	int currSpeed = GAME_START_SPEED;
	int speedCnt = 0;
	int score = 0;
	bool gameRunning = false;
	bool refreshDisplay = false;
	bool refreshScore = false;

	int snakeLength = 3;
	int snakeX[216];
	int snakeY[216];
	Dir_t snakeDir = DOWN;
	int foodX;
	int foodY;

	RGBColor snakeColor = RGBColor(0, 0, 255);
	RGBColor headColor = RGBColor(0, 100, 255);
	RGBColor foodColor = RGBColor(255, 128, 0);

	void moveSnake();
	void placeNewFood();
	bool isInSnake(int x, int y, bool ignoreHead);
};

#endif