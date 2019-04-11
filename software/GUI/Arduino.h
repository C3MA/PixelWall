#ifndef ARDUINO_H
#define ARDUINO_H

#define String String^
#define HIGH 1
#define LOW 0

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
using namespace System;

#define digitalWrite(x, y) {}

void strcpy(char *dest, char *src);
int random(int min, int max);

#endif