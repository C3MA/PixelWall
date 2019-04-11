#include "ARGBColor.h"

ARGBColor::ARGBColor()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->trans = true;
}

ARGBColor::ARGBColor(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->trans = false;
}

ARGBColor::ARGBColor(const RGBColor* const color)
{
	this->r = color->r;
	this->g = color->g;
	this->b = color->b;
	this->trans = false;
}

RGBColor ARGBColor::ToRGB()
{
	return RGBColor(r, g, b);
}