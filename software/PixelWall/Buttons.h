#pragma once

class Buttons 
{
	public:

	typedef enum Button_t{
		NONE,
		APP_SELECT,
		APP_UP,
		APP_DOWN,
		NES_UP,
		NES_RIGHT,
		NES_DOWN,
		NES_LEFT,
		NES_SELECT,
		NES_START,
		NES_A,
		NES_B
	};

	typedef enum Event_t{
		DOWN,
		UP
	};

	typedef struct ButtonEvent_t{
		Button_t button;
		Event_t event;
	};

	void init();
	ButtonEvent_t getPressedButton();
	bool buttonModulPresent();

	private:
		int lastAppSelect;
		int lastAppUp;
		int lastAppDown;

		int lastNesState;
		int lastNesA;
		int lastNesB;
		int lastNesStart;
		int lastNesSelect;
		int lastNesUp;
		int lastNesRight;
		int lastNesLeft;
		int lastNesDown;

		ButtonEvent_t readAppButtons();
		int readOutNesController();
		ButtonEvent_t readNesButtons();
};