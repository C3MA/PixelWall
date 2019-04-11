#include "RGBColor.h"

RGBColor::RGBColor()
{
	RGBColor(0, 0, 0);
}

RGBColor::RGBColor(int r, int g, int b)
{
	this->r = r;
    this->g = g;
    this->b = b;
}
