#ifndef WEBSITES_H
#define WEBSITES_H

#include <Arduino.h>

typedef struct {
	unsigned int statusCode;
    const char* header1;
    char title[20];
    const char* header2;
    const char* body;
}WebsiteResponse_t;

class WebSites
{
    public:
        static String getHeader404(int responseLength);
        static String getHeader200(int responseLength, String contentType);

		static String getContentSettings(String ssid, String pass);

		static const char empty[];
        static const char HTMLError404[];
        static const char HTMLHeader1[];
		static const char HTMLHeader1NoWs[];
        static const char HTMLHeader2[];
		static const char HTMLHeader2NoWs[];

        static const char HTMLDefault[];
        static const char HTMLImages[];
        static const char HTMLPixelIt[];
        static const char HTMLTetris[];
        static const char HTMLClock[];
        static const char HTMLSpaceInvaders[];
		static const char HTMLSnake[];

		static const WebsiteResponse_t errorPage404;

};

#endif