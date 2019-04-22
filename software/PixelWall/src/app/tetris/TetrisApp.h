#ifndef TETRIS_APP_H
#define TETRIS_APP_H

#include "../IPixelApp.h"
#include "../../LedPanel.h"
#include "Stones.h"

class TetrisApp :public IPixelApp
{
    public:
	TetrisApp(LedPanel* panelPnt, void(*sendWebsocketDataCb)(char* payload, uint8_t len));
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
    void drawStone(int col, int row, IStone* stone, unsigned int layer);
	void moveDown();
	bool currStoneIsMoveable(unsigned int col, unsigned int row);
	void loadNextStone();
	void rotate();
	void deleteFullRows();
    void sendScore();
	void gameOver();

	void(*sendWebsocketData)(char* payload, uint8_t len);

    LedPanel* panel;
	Stones stones;
    IStone currStone;
	int currStoneArr[6] = { 0,0,0,0,0,0 };

	const int GAME_START_SPEED = 80;
    const int FAST_DOWN_SPEED = 5;
	int currSpeed = GAME_START_SPEED;
	int gameSpeed = GAME_START_SPEED;
	int speedCnt = 0;
    int currStoneX = 5;
    int currStoneY = 0;
	int score = 0;
	bool gameRunning = false;
	bool refreshDisplay = false;
	bool refreshScore = false;
};

#endif