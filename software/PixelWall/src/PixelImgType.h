#ifndef PIXEL_IMG_TYPE
#define PIXEL_IMG_TYPE

#include "ARGBColor.h"

class IPixelImage
{
public:
	IPixelImage() {};
	IPixelImage(int width, int height, int* imgData)
	{
		this->width = width;
		this->height = height;
		this->imgData = imgData;
	}

	unsigned int width;
	unsigned int height;
	int* imgData;
};

class IPictureImage
{
public:
	unsigned int width;
	unsigned int height;
	ARGBColor* imgData;
};

class Digits
{
public:
	IPixelImage zero;
	IPixelImage one;
	IPixelImage two;
	IPixelImage three;
	IPixelImage four;
	IPixelImage five;
	IPixelImage six;
	IPixelImage seven;
	IPixelImage eight;
	IPixelImage nine;

	Digits()
	{
		zero.imgData = zeroArr;
		zero.width = 3;
		zero.height = 5;

		one.imgData = oneArr;
		one.width = 3;
		one.height = 5;

		two.imgData = twoArr;
		two.width = 3;
		two.height = 5;

		three.imgData = threeArr;
		three.width = 3;
		three.height = 5;

		four.imgData = fourArr;
		four.width = 3;
		four.height = 5;

		five.imgData = fiveArr;
		five.width = 3;
		five.height = 5;

		six.imgData = sixArr;
		six.width = 3;
		six.height = 5;

		seven.imgData = sevenArr;
		seven.width = 3;
		seven.height = 5;

		eight.imgData = eightArr;
		eight.width = 3;
		eight.height = 5;

		nine.imgData = nineArr;
		nine.width = 3;
		nine.height = 5;
	}

private :
	int zeroArr[15] = { 1,1,1,1,0,1,1,0,1,1,0,1,1,1,1 };
	int oneArr[15] = { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 };
	int twoArr[15] = { 1, 1, 1,0, 0, 1,1, 1, 1,1, 0, 0, 1, 1, 1 };
	int threeArr[15] = { 1, 1, 1,0, 0, 1,1, 1, 1,0, 0, 1,1, 1, 1 };
	int fourArr[15] = { 1, 0, 1,1, 0, 1,1, 1, 1,0, 0, 1,0, 0, 1 };
	int fiveArr[15] = { 1, 1, 1,1, 0, 0,1, 1, 1,0, 0, 1,1, 1, 1 };
	int sixArr[15] = { 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1 };
	int sevenArr[15] = { 1, 1, 1,0, 0, 1,0, 0, 1,0, 0, 1,0, 0, 1 };
	int eightArr[15] = { 1, 1, 1,1, 0, 1,1, 1, 1,1, 0, 1,1, 1, 1 };
	int nineArr[15] = { 1, 1, 1,1, 0, 1,1, 1, 1,0, 0, 1,1, 1, 1 };
};

class Letters
{
public:
	IPixelImage a = IPixelImage(3, 5, aArr);
	IPixelImage b = IPixelImage(3, 5, bArr);;
	IPixelImage c = IPixelImage(3, 5, cArr);;
	IPixelImage d = IPixelImage(3, 5, dArr);;
	IPixelImage e = IPixelImage(3, 5, eArr);;
	IPixelImage f = IPixelImage(3, 5, fArr);;
	IPixelImage g = IPixelImage(3, 5, gArr);;
	IPixelImage h = IPixelImage(3, 5, hArr);;
	IPixelImage i = IPixelImage(3, 5, iArr);;
	IPixelImage j = IPixelImage(3, 5, jArr);;
	IPixelImage k = IPixelImage(3, 5, kArr);;
	IPixelImage l = IPixelImage(3, 5, lArr);;
	IPixelImage o = IPixelImage(3, 5, oArr);;
	IPixelImage p = IPixelImage(3, 5, pArr);;
	IPixelImage r = IPixelImage(3, 5, rArr);;
	IPixelImage s = IPixelImage(3, 5, sArr);;
	IPixelImage t = IPixelImage(3, 5, tArr);;
	IPixelImage u = IPixelImage(3, 5, uArr);;
	IPixelImage x = IPixelImage(3, 5, xArr);;

private:
	int aArr[15] = { 1,1,1,1,0,1,1,1,1,1,0,1,1,0,1 };
	int bArr[15] = { 1,1,0,1,0,1,1,1,0,1,0,1,1,1,0 };
	int cArr[15] = { 1,1,1,1,0,0,1,0,0,1,0,0,1,1,1 };
	int dArr[15] = { 1,1,0,1,0,1,1,0,1,1,0,1,1,1,0 };
	int eArr[15] = { 1,1,1,1,0,0,1,1,0,1,0,0,1,1,1 };
	int fArr[15] = { 1,1,1,1,0,0,1,1,0,1,0,0,1,0,0 };
	int gArr[15] = { 1,1,1,1,0,0,1,0,1,1,0,1,1,1,1 };
	int hArr[15] = { 1,0,1,1,0,1,1,1,1,1,0,1,1,0,1 };
	int iArr[15] = { 0,1,0,0,1,0,0,1,0,0,1,0,0,1,0 };
	int jArr[15] = { 0,0,1,0,0,1,0,0,1,1,0,1,0,1,1 };
	int kArr[15] = { 1,0,1,1,1,0,1,0,0,1,1,0,1,0,1 };
	int lArr[15] = { 1,0,0,1,0,0,1,0,0,1,0,0,1,1,1 };
	int oArr[15] = { 1,1,1,1,0,1,1,0,1,1,0,1,1,1,1 };
	int pArr[15] = { 1,1,1,1,0,1,1,1,1,1,0,0,1,0,0 };
	int rArr[15] = { 1,1,1,1,0,1,1,1,1,1,1,0,1,0,1 };
	int sArr[15] = { 0,1,1,1,0,0,0,1,0,0,0,1,1,1,0 };
	int tArr[15] = { 1,1,1,0,1,0,0,1,0,0,1,0,0,1,0 };
	int uArr[15] = { 1,0,1,1,0,1,1,0,1,1,0,1,1,1,1 };
	int xArr[15] = { 0,0,0,0,0,0,1,0,1,0,1,0,1,0,1 };

};

class Icons
{
public:
	IPixelImage smiley;
	IPixelImage badSmiley;
	IPixelImage badSmileySmall;
	IPixelImage wlan;
	IPixelImage tick;
	IPixelImage cross;

	Icons()
	{
		smiley.imgData = smileyArr;
		smiley.width = 8;
		smiley.height = 8;

		badSmiley.imgData = badSmileyArr;
		badSmiley.width = 8;
		badSmiley.height = 8;

		badSmileySmall.imgData = badSmileySmallArr;
		badSmileySmall.width = 6;
		badSmileySmall.height = 4;

		wlan.imgData = wlanArr;
		wlan.width = 7;
		wlan.height = 5;

		tick.imgData = tickArr;
		tick.width = 3;
		tick.height = 3;

		cross.imgData = crossArr;
		cross.width = 3;
		cross.height = 3;
	}

private :
	int smileyArr[64] = { 0,0,1,1,1,1,0,0,
					   0,1,0,0,0,0,1,0,
					   1,0,1,0,0,1,0,1,
					   1,0,0,0,0,0,0,1,
					   1,0,1,0,0,1,0,1,
					   1,0,0,1,1,0,0,1,
					   0,1,0,0,0,0,1,0,
					   0,0,1,1,1,1,0,0 };

	int badSmileyArr[64] = {0,0,1,1,1,1,0,0,
							0,1,0,0,0,0,1,0,
							1,0,1,0,0,1,0,1,
							1,0,0,0,0,0,0,1,
							1,0,0,1,1,0,0,1,
							1,0,1,0,0,1,0,1,
							0,1,0,0,0,0,1,0,
							0,0,1,1,1,1,0,0 };
	
	int badSmileySmallArr[24] = { 0,1,0,0,1,0,
								  0,0,0,0,0,0,
								  0,1,1,1,1,0,
								  1,0,0,0,0,1 };


	int wlanArr[35] = { 0,1,1,1,1,1,0,
						1,0,0,0,0,0,1,
						0,0,1,1,1,0,0,
						0,0,0,0,0,0,0,
						0,0,0,1,0,0,0 };

	int tickArr[9] = { 1,0,1,
					 	1,1,0,
					 	1,0,0 };

	int crossArr[9] = { 1,0,1,
					 	0,1,0,
					 	1,0,1 };
};


#endif