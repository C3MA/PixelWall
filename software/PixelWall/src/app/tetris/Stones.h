#ifndef STONES_H
#define STONES_H

#include "../../RGBColor.h"
#include <string.h>

class IStone
{
public:
	int width;
	int height;
	RGBColor color;
	int imgData[6];
};

class Stones
{
public:
	IStone stone[7];
	int stone0[6] = { 1,1,1,0,1,0 };
	int stone1[4] = { 1,1,1,1 };
	int stone2[4] = { 1,1,1,1 };
	int stone3[6] = { 0,1,1,1,1,0 };
	int stone4[6] = { 1,0,1,1,0,1 };
	int stone5[6] = { 1,1,1,0,0,1 };
	int stone6[6] = { 0,0,1,1,1,1 };

	Stones()
	{
		memcpy(stone[0].imgData, stone0, 6*(sizeof(int)));
		stone[0].width = 3;
		stone[0].height = 2;
		stone[0].color = RGBColor(255, 0, 255);

		memcpy(stone[1].imgData, stone1, 6 * (sizeof(int)));
		stone[1].width = 2;
		stone[1].height = 2;
		stone[1].color = RGBColor(255, 255, 0);

		memcpy(stone[2].imgData, stone2, 6 * (sizeof(int)));
		stone[2].width = 1;
		stone[2].height = 4;
		stone[2].color = RGBColor(0, 255, 255);

		memcpy(stone[3].imgData, stone3, 6 * (sizeof(int)));
		stone[3].width = 2;
		stone[3].height = 3;
		stone[3].color = RGBColor(255, 0, 0);

		memcpy(stone[4].imgData, stone4, 6 * (sizeof(int)));
		stone[4].width = 2;
		stone[4].height = 3;
		stone[4].color = RGBColor(0, 255, 0);

		memcpy(stone[5].imgData, stone5, 6 * (sizeof(int)));
		stone[5].width = 3;
		stone[5].height = 2;
		stone[5].color = RGBColor(0, 0, 255);

		memcpy(stone[6].imgData, stone6, 6 * (sizeof(int)));
		stone[6].width = 3;
		stone[6].height = 2;
		stone[6].color = RGBColor(255, 128, 0);
	}
};

#endif