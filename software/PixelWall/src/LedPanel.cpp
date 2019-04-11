/*
 * Übergeordnete Funktionen für die LED-Matrix
 * - Zahlen anzeigen
 * - Bestimmte Texte anzeigen
 * - vordefinierte Icons anzeigen
 * - Layer Abbildung
 */

#include "LedPanel.h"
#include "PixelImgType.h"

void LedPanel::printImage(IPixelImage image, unsigned int col, unsigned int row, RGBColor color, bool transparent, unsigned int layer)
{
	for (unsigned int y = 0; y < image.height; y++)
	{
		for (unsigned int x = 0; x < image.width; x++)
		{
			if (image.imgData[x + y * image.width] == 1)
			{
				setLed(col + x, row + y, color, layer);
			}
			else
			{
				if (!transparent)
					clearLed(col + x, row + y, layer);
			}
		}
	}
}

void LedPanel::printDigit(unsigned int digit, unsigned int col, unsigned int row, RGBColor color, bool transparent, unsigned int layer)
{
    Digits digits;

    if(digit == 0) printImage(digits.zero,col,row,color,transparent, layer);
    else if(digit == 1) printImage(digits.one,col,row,color,transparent, layer);
    else if(digit == 2) printImage(digits.two,col,row,color,transparent, layer);
    else if(digit == 3) printImage(digits.three,col,row,color,transparent, layer);
    else if(digit == 4) printImage(digits.four,col,row,color,transparent, layer);
    else if(digit == 5) printImage(digits.five,col,row,color,transparent, layer);
    else if(digit == 6) printImage(digits.six,col,row,color,transparent, layer);
    else if(digit == 7) printImage(digits.seven,col,row,color,transparent, layer);
    else if(digit == 8) printImage(digits.eight,col,row,color,transparent, layer);
    else if(digit == 9) printImage(digits.nine,col,row,color,transparent, layer);
}

void LedPanel::printFormatedNumber(int num, unsigned int numOfMinDigits, unsigned int col, unsigned int row, RGBColor color, unsigned int layer)
{
	if (num < 10)
	{
		//einstellige Zahl:
		if(numOfMinDigits==2)
		{
			printDigit(0, col, row, color, false, layer);
			printDigit(num, col + 4, row, color, false, layer);
		}
		else if(numOfMinDigits==3)
		{
			printDigit(0, col, row, color, false, layer);
			printDigit(0, col+4, row, color, false, layer);
			printDigit(num, col + 8, row, color, false, layer);
		}
		else
		{
			printDigit(num, col, row, color, false, layer);
		}

	}
	else if (num < 100)
	{
		//zweistellige Zahl
		if(numOfMinDigits==3)
		{
			printDigit(0, col, row, color, false, layer);
			printDigit((num/10), col+4, row, color, false, layer);
			printDigit((num%10), col+8, row, color, false, layer);
		}
		else
		{
			printDigit((num/10), col, row, color, false, layer);
			printDigit((num%10), col+4, row, color, false, layer);
		}
	}
	else
	{
		//dreistellige Zahl
		printDigit((num/100), col, row, color, false, layer);	//hunderter
		num = num % 100;
		printDigit((num/10), col+4, row, color, false, layer);	//zehner
		printDigit((num%10), col+8, row, color, false, layer);	//einer
	}

}

void LedPanel::printNumber(int num, unsigned int col, unsigned int row, RGBColor color, unsigned int layer)
{
	if (num < 10)
	{
		printDigit(num, col, row, color, false, layer);
	}
	else if (num < 100)
	{
		printDigit((num / 10), col, row, color, false, layer);
		printDigit((num % 10), col + 4, row, color, false, layer);
	}
	else if (num < 1000)
	{
		//dreistellige Zahl
		printDigit((num / 100), col, row, color, false, layer);	//hunderter
		num = num % 100;
		printDigit((num / 10), col + 4, row, color, false, layer);	//zehner
		printDigit((num % 10), col + 8, row, color, false, layer);	//einer
	}
	else if (num < 10000)
	{
		//vierstellige Zahl
		printDigit((num / 1000), col, row, color, false, layer);	//tausender
		num = num % 1000;
		printDigit((num / 100), col, row + 6, color, false, layer);	//hunderter
		num = num % 100;
		printDigit((num / 10), col + 4, row + 6, color, false, layer);	//zehner
		printDigit((num % 10), col + 8, row + 6, color, false, layer);	//einer
	}
	else if (num < 100000)
	{
		//fünfstellige Zahl
		printDigit((num / 10000), col, row, color, false, layer);	//zehntausender
		num = num % 10000;
		printDigit((num / 1000), col + 4, row, color, false, layer);	//tausender
		num = num % 1000;
		printDigit((num / 100), col, row + 6, color, false, layer);	//hunderter
		num = num % 100;
		printDigit((num / 10), col + 4, row + 6, color, false, layer);	//zehner
		printDigit((num % 10), col + 8, row + 6, color, false, layer);	//einer
	}
	else
	{
		//sechsstellige Zahl
		printDigit((num / 100000), col, row, color, false, layer);	//hunderttausender
		num = num % 100000;
		printDigit((num / 10000), col+4, row, color, false, layer);	//zehntausender
		num = num % 10000;
		printDigit((num / 1000), col + 8, row, color, false, layer);	//tausender
		num = num % 1000;
		printDigit((num / 100), col, row + 6, color, false, layer);	//hunderter
		num = num % 100;
		printDigit((num / 10), col + 4, row + 6, color, false, layer);	//zehner
		printDigit((num % 10), col + 8, row + 6, color, false, layer);	//einer
	}

}

void LedPanel::printLineH(unsigned int col, unsigned int row, unsigned int num, RGBColor color, unsigned int layer)
{
	for (unsigned int x = col; x < num+col; x++)
	{
		setLed(x, row, color, layer);
	}
}

void LedPanel::printLineV(unsigned int col, unsigned int row, unsigned int num, RGBColor color, unsigned int layer)
{
	for (unsigned int y = row; y < num + row; y++)
	{
		setLed(col, y, color, layer);
	}
}

void LedPanel::clear(unsigned int layer)
{
	for (unsigned int y = 0; y < ROWS; y++)
	{
		for (unsigned int x = 0; x < COLS; x++)
		{
			if (layer == 0)
				layer0[x][y].trans = true;
			else
				layer1[x][y].trans = true;
		}
	}
}

void LedPanel::clear()
{
	clear(0);
	clear(1);
}

void LedPanel::setAll(RGBColor color, unsigned int layer)
{
	for (unsigned int y = 0; y < ROWS; y++)
	{
		for (unsigned int x = 0; x < COLS; x++)
		{
			setLed(x, y, color, layer);
		}
	}
}

void LedPanel::show()
{
	
	for (unsigned y = 0; y < ROWS; y++)
	{
		for (unsigned x = 0; x < COLS; x++)
		{
			if (layer1[x][y].trans == false)
			{
				ledMatrix.setLed(x, y, layer1[x][y].ToRGB());
			}
			else
			{
				if (layer0[x][y].trans == false)
				{ 
					ledMatrix.setLed(x, y, layer0[x][y].ToRGB());
				}
				else
				{
					ledMatrix.clearLed(x, y);
				}

			}
		}
	}
	
	ledMatrix.show();
}



void LedPanel::setLed(unsigned int col, unsigned int row, RGBColor color, unsigned int layer)
{
	if (col < COLS && row < ROWS)
	{
		if (layer == 0)
			layer0[col][row] = ARGBColor(&color);

		if (layer == 1)
			layer1[col][row] = ARGBColor(&color);
	}
}

void LedPanel::clearLed(unsigned int col, unsigned int row, unsigned int layer)
{
	if (col < COLS && row < ROWS)
	{
		if (layer == 0)
			layer0[col][row].trans = true;

		if (layer == 1)
			layer1[col][row].trans = true;
	}
}

bool LedPanel::isSet(unsigned int col, unsigned int row, unsigned int layer)
{
	if (col >= COLS) return false;
	if (row >= ROWS) return false;

	if (layer == 0)
		return !layer0[col][row].trans;
	else
		return !layer1[col][row].trans;
}

void LedPanel::clearRow(unsigned int row, unsigned int layer)
{
	for (unsigned int x = 0; x < COLS; x++)
	{
		clearLed(x, row, layer);
	}
}

void LedPanel::clearRowAndFall(unsigned int row, unsigned int layer)
{
	for (int y = row; y > 0; y--)
	{
		for (unsigned int x = 0; x < COLS; x++)
		{
			if (layer == 0)
				layer0[x][y] = layer0[x][y - 1];
			else
				layer1[x][y] = layer1[x][y - 1];

		}
	}
}