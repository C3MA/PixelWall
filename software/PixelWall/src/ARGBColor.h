#ifndef ARGB_COLOR_H
#define ARGB_COLOR_H

#include "RGBColor.h"

class ARGBColor: RGBColor
{
public:
	bool trans = false;
	ARGBColor();
	ARGBColor(int r, int g, int b);
	ARGBColor(const RGBColor* const color);
	RGBColor ToRGB();
};

#endif