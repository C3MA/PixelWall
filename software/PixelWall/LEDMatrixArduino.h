#pragma once

#include "src/RGBColor.h"
#include <Adafruit_NeoPixel.h>

#define WS2812_PIN    2
#define NUMPIXELS     216

class LEDMatrix
{
private:
	RGBColor* ledBuf = new RGBColor[216];
	Adafruit_NeoPixel pixels;
	int brightness = 100;

public:
	int COLS = 12;
	int ROWS = 18;

	LEDMatrix();

	void setBrightness(unsigned int brightness);

	void setLed(unsigned int col, unsigned int row, RGBColor color);
	void setAll(RGBColor color);

	void clearLed(unsigned int col, unsigned int row);
	void clearAll();

	void show();

	void test();
};

