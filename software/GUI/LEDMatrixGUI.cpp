#include "LEDMatrixGUI.h"

void LEDMatrix::setLabel(array<System::Windows::Forms::Label^, 1>^ labels)
{
	guiLabels = labels;
}

void LEDMatrix::setLed(unsigned int col, unsigned int row, RGBColor color)
{
	unsigned int index = row * COLS + col;
	ledBuf[index] = color;
}

void LEDMatrix::setAll(RGBColor color)
{
	int index;

	for (unsigned int y = 0; y < ROWS; y++)
	{
		for (unsigned int x = 0; x < COLS; x++)
		{
			index = y * COLS + x;
			ledBuf[index] = color;
		}
	}
}

void LEDMatrix::clearLed(unsigned int col, unsigned int row)
{
	int index = row * COLS + col;
	ledBuf[index] = RGBColor(0,0,0);
}

void LEDMatrix::clearAll()
{
	unsigned int index;

	for (unsigned int y = 0; y < ROWS; y++)
	{
		for (unsigned int x = 0; x < COLS; x++)
		{
			index = y * COLS + x;
			ledBuf[index] = RGBColor(0,0,0);
		}
	}
}

void LEDMatrix::show()
{
	unsigned int index;
	
	for (unsigned int y = 0; y < ROWS; y++)
	{
		for (unsigned int x = 0; x < COLS; x++)
		{
			index = y * COLS + x;
			guiLabels[index]->BackColor = System::Drawing::Color::FromArgb(ledBuf[index].r * brightness / 100, ledBuf[index].g * brightness / 100, ledBuf[index].b * brightness / 100);
		}
	}
}