#ifndef PARAMETER_H
#define PARAMETER_H

#include <Arduino.h>

class Parameter
{
public:
	static char param_ssid[50];
	static char param_pass[50];
	static char lastAppIndex;

	static void load();
	static void save();
};


#endif