#ifndef LED_PANEL_H
#define LED_PANEL_H

/*
 * Übergeordnete Funktionen für die LED-Matrix
 * - Zahlen anzeigen
 * - Bestimmte Texte anzeigen
 * - vordefinierte Icons anzeigen
 * - Layer Abbildung
 */

#ifdef ARDUINO
#include "../LEDMatrixArduino.h"
#else
#include <LEDMatrixGUI.h>
#endif
#include "PixelImgType.h"
#include "ARGBColor.h"

class LedPanel
{
public:
	static const unsigned int COLS = 12;
	static const unsigned int ROWS = 18;
	LEDMatrix ledMatrix;
	Icons icons;
	Letters letters;
	ARGBColor layer0[COLS][ROWS];
	ARGBColor layer1[COLS][ROWS];

	void setLed(unsigned int col, unsigned int row, RGBColor color, unsigned int layer);
	void clearLed(unsigned int col, unsigned int row, unsigned int layer);
	bool isSet(unsigned int col, unsigned int row, unsigned int layer);
	void clear(unsigned int layer);
	void clear();
	void setAll(RGBColor color, unsigned int layer);
	void clearRow(unsigned int row, unsigned int layer);


	void clearRowAndFall(unsigned int row, unsigned int layer);


	void printImage(IPixelImage image, unsigned int col, unsigned int row, RGBColor color, bool transparent, unsigned int layer);
	void printDigit(unsigned int digit, unsigned int col, unsigned int row, RGBColor color, bool transparent, unsigned int layer);
	void printFormatedNumber(int num, unsigned int numOfMinDigits, unsigned int col, unsigned int row, RGBColor color, unsigned int layer);
	void printNumber(int num, unsigned int col, unsigned int row, RGBColor color, unsigned int layer);
	void printLineH(unsigned int col, unsigned int row, unsigned int num, RGBColor color, unsigned int layer);
	void printLineV(unsigned int col, unsigned int row, unsigned int num, RGBColor color, unsigned int layer);

	void show();

private:
	

};

#endif