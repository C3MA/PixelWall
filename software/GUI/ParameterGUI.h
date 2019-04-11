#pragma once

#include <Arduino.h>

ref class Parameter
{
public:
	static String param_ssid = "test";
	static String param_pass = "trs";

	static void load() {};
	static void save() {};
};