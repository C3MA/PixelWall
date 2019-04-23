#include "Buttons.h"
#include <Arduino.h>

//pin definitions:
#define PIN_APP_SELECT 		5
#define PIN_APP_UP 			4
#define PIN_APP_DOWN 		12
#define PIN_NES_DATA		13
#define PIN_NES_LATCH		14
#define PIN_NES_CLK			15
#define PIN_DETECT			16

//masks for NES controller
#define MASK_BTN_A 			0x80
#define MASK_BTN_B 			0x40
#define MASK_BTN_START 		0x10
#define MASK_BTN_SELECT 	0x20
#define MASK_BTN_UP 		0x08
#define MASK_BTN_RIGHT 		0x01
#define MASK_BTN_DOWN 		0x04
#define MASK_BTN_LEFT 		0x02


void Buttons::init()
{
	pinMode(PIN_APP_SELECT, INPUT_PULLUP);
	pinMode(PIN_APP_UP, INPUT_PULLUP);
	pinMode(PIN_APP_DOWN, INPUT_PULLUP);
	pinMode(PIN_DETECT, INPUT_PULLUP);	//Pull down?

	pinMode(PIN_NES_LATCH, OUTPUT);
	pinMode(PIN_NES_CLK, OUTPUT);
	pinMode(PIN_NES_DATA, INPUT);

	digitalWrite(PIN_NES_CLK, HIGH);
	digitalWrite(PIN_NES_LATCH, LOW);

	lastAppSelect = HIGH;
	lastAppUp = HIGH;
	lastAppDown = HIGH;
}

Buttons::ButtonEvent_t Buttons::getPressedButton()
{
	ButtonEvent_t tmpButtonEvent;
	
	tmpButtonEvent = readAppButtons();
	
	if(tmpButtonEvent.button == NONE)
		tmpButtonEvent = readNesButtons();

	return tmpButtonEvent;
}

bool Buttons::buttonModulPresent()
{
	return (digitalRead(PIN_DETECT) == HIGH);
}

Buttons::ButtonEvent_t Buttons::readNesButtons()
{
	ButtonEvent_t tmpEvent;
	int tmpState = readOutNesController();

	if(tmpState == lastNesState)
	{
		tmpEvent.button = NONE;
	}
	else
	{
		lastNesState = tmpState;

		if((tmpState & MASK_BTN_A) != lastNesA)
		{
			//something has changed
			lastNesA = (tmpState & MASK_BTN_A);
			tmpEvent.button = NES_A;
			
			if(lastNesA)
			{
				tmpEvent.event = DOWN;
			}
			else
			{
				tmpEvent.event = UP;
			}
			return tmpEvent;
		}

		if((tmpState & MASK_BTN_B) != lastNesB)
		{
			//something has changed
			lastNesB = (tmpState & MASK_BTN_B);
			tmpEvent.button = NES_B;
			
			if(lastNesB)
			{
				tmpEvent.event = DOWN;
			}
			else
			{
				tmpEvent.event = UP;
			}
			return tmpEvent;
		}

		if((tmpState & MASK_BTN_START) != lastNesStart)
		{
			//something has changed
			lastNesStart = (tmpState & MASK_BTN_START);
			tmpEvent.button = NES_START;
			
			if(lastNesStart)
			{
				tmpEvent.event = DOWN;
			}
			else
			{
				tmpEvent.event = UP;
			}
			return tmpEvent;
		}

		if((tmpState & MASK_BTN_SELECT) != lastNesSelect)
		{
			//something has changed
			lastNesSelect = (tmpState & MASK_BTN_SELECT);
			tmpEvent.button = NES_SELECT;
			
			if(lastNesSelect)
			{
				tmpEvent.event = DOWN;
			}
			else
			{
				tmpEvent.event = UP;
			}
			return tmpEvent;
		}

		if((tmpState & MASK_BTN_UP) != lastNesUp)
		{
			//something has changed
			lastNesUp = (tmpState & MASK_BTN_UP);
			tmpEvent.button = NES_UP;
			
			if(lastNesUp)
			{
				tmpEvent.event = DOWN;
			}
			else
			{
				tmpEvent.event = UP;
			}
			return tmpEvent;
		}

		if((tmpState & MASK_BTN_RIGHT) != lastNesRight)
		{
			//something has changed
			lastNesRight = (tmpState & MASK_BTN_RIGHT);
			tmpEvent.button = NES_RIGHT;
			
			if(lastNesRight)
			{
				tmpEvent.event = DOWN;
			}
			else
			{
				tmpEvent.event = UP;
			}
			return tmpEvent;
		}

		if((tmpState & MASK_BTN_DOWN) != lastNesDown)
		{
			//something has changed
			lastNesDown = (tmpState & MASK_BTN_DOWN);
			tmpEvent.button = NES_DOWN;
			
			if(lastNesDown)
			{
				tmpEvent.event = DOWN;
			}
			else
			{
				tmpEvent.event = UP;
			}
			return tmpEvent;
		}

		if((tmpState & MASK_BTN_LEFT) != lastNesLeft)
		{
			//something has changed
			lastNesLeft = (tmpState & MASK_BTN_LEFT);
			tmpEvent.button = NES_LEFT;
			
			if(lastNesLeft)
			{
				tmpEvent.event = DOWN;
			}
			else
			{
				tmpEvent.event = UP;
			}
			return tmpEvent;
		}
		
	}

	return tmpEvent;
	
}

int Buttons::readOutNesController()
{
	int result = 0;

	digitalWrite(PIN_NES_LATCH, HIGH);
	delayMicroseconds(50);
	digitalWrite(PIN_NES_LATCH, LOW);
	if(digitalRead(PIN_NES_DATA)==LOW)
		result |= 1;
	delayMicroseconds(50);
	for(int i = 0; i < 7; i++)
	{
		digitalWrite(PIN_NES_CLK, HIGH);
		delayMicroseconds(50);
		digitalWrite(PIN_NES_CLK, LOW);
		result <<= 1;
		if(digitalRead(PIN_NES_DATA)==LOW)
			result |= 1;
		
		delayMicroseconds(50);
	}

	digitalWrite(PIN_NES_CLK, HIGH);
	delayMicroseconds(50);
	digitalWrite(PIN_NES_CLK, LOW);

	return result;
}

Buttons::ButtonEvent_t Buttons::readAppButtons()
{
	Buttons::ButtonEvent_t tmpEvent;
	int tmpState = digitalRead(PIN_APP_SELECT);

	if(tmpState != lastAppSelect)
	{
		//something has changed
		lastAppSelect = tmpState;
		tmpEvent.button = APP_SELECT;
		
		if(tmpState==LOW)
		{
			tmpEvent.event = DOWN;
		}
		else if(tmpState==HIGH)
		{
			tmpEvent.event = UP;
		}
		return tmpEvent;
	}

	tmpState = digitalRead(PIN_APP_UP);

	if(tmpState != lastAppUp)
	{
		//something has changed
		lastAppUp = tmpState;
		tmpEvent.button = APP_UP;

		if(tmpState==LOW)
		{
			tmpEvent.event = DOWN;
		}
		else if(tmpState==HIGH)
		{
			tmpEvent.event = UP;
		}

		return tmpEvent;
	}

	tmpState = digitalRead(PIN_APP_DOWN);

	if(tmpState != lastAppDown)
	{
		//something has changed
		lastAppDown = tmpState;
		tmpEvent.button = APP_DOWN;

		if(tmpState==LOW)
		{
			tmpEvent.event = DOWN;
		}
		else if(tmpState==HIGH)
		{
			tmpEvent.event = UP;
		}

		return tmpEvent;
	}

	//nothing was pressed or released
	tmpEvent.button = NONE;
	return tmpEvent;
}