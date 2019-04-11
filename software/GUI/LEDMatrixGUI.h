#pragma once

#include "RGBColor.h"

#include <gcroot.h>

class LEDMatrix
{
private:
	gcroot<array<System::Windows::Forms::Label^, 1>^> guiLabels;
	RGBColor* ledBuf = new RGBColor[216];

public:
	unsigned int COLS = 12;
	unsigned int ROWS = 18;
	unsigned int brightness = 100;

	void setLabel(array<System::Windows::Forms::Label^, 1>^ labels);

	void setLed(unsigned int col, unsigned int row, RGBColor color);
	void setAll(RGBColor color);

	void clearLed(unsigned int col, unsigned int row);
	void clearAll();

	void show();
};

