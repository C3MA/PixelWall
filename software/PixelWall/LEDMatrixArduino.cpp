#include "LEDMatrixArduino.h"

LEDMatrix::LEDMatrix():
	pixels(NUMPIXELS, WS2812_PIN, NEO_GRB + NEO_KHZ800)
{
	pixels.begin(); // This initializes the NeoPixel library.
}

void LEDMatrix::setBrightness(unsigned int brightness)
{
	this->brightness = brightness;
	show();
}

void LEDMatrix::setLed(unsigned int col, unsigned int row, RGBColor color)
{
	unsigned int index = row * COLS + col;
	ledBuf[index] = color;
}

void LEDMatrix::setAll(RGBColor color)
{
	int index;

	for (int y = 0; y < ROWS; y++)
	{
		for (int x = 0; x < COLS; x++)
		{
			index = y * COLS + x;
			ledBuf[index] = color;
		}
	}
}

void LEDMatrix::clearLed(unsigned int col, unsigned int row)
{
	unsigned int index = row * COLS + col;
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
	unsigned int neoPixelIndex;
	digitalWrite(4, HIGH);
	for (unsigned int y = 0; y < ROWS; y++)
	{
		for (unsigned int x = 0; x < COLS; x++)
		{
			index = y * COLS + x;

			if(y == 1 || y == 4 || y == 7 || y == 10 || y == 13 || y == 16)
			{
				neoPixelIndex = y * COLS + (COLS-x-1);
			}
			else
			{
				neoPixelIndex = index;
			}

			//guiLabels[index]->BackColor = System::Drawing::Color::FromArgb(ledBuf[index].r * brightness / 100, ledBuf[index].g * brightness / 100, ledBuf[index].b * brightness / 100);
			pixels.setPixelColor(neoPixelIndex, pixels.Color((ledBuf[index].r * brightness) / 100,(ledBuf[index].g * brightness) / 100,(ledBuf[index].b * brightness) / 100));
		}
	}
    pixels.show(); // This sends the updated pixel color to the hardware.
	digitalWrite(4, LOW);
}

void LEDMatrix::test()
{
	for(unsigned int i=0;i<NUMPIXELS;i++)
	{
		pixels.setPixelColor(i, pixels.Color(30,30,30)); // Moderately bright green color.
		pixels.show(); // This sends the updated pixel color to the hardware.
		delay(150); // Delay for a period of time (in milliseconds).
	}
}
