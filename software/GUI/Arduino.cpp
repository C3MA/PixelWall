#include "Arduino.h"

#include <gcroot.h>

gcroot<Random^> myRandom = gcnew Random();

void strcpy(char *dest, char *src)
{
	char * tmpdest = dest;
	while (*src != 0)
	{
		*tmpdest = *src;
		src++;
		tmpdest++;
	}
	*tmpdest = 0;
}

int random(int min, int max)
{
	return myRandom->Next(min, max);
}