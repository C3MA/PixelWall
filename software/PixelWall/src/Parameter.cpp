#include "Parameter.h"
#include <EEPROM.h>

char Parameter::param_ssid[];
char Parameter::param_pass[];
char Parameter::lastAppIndex;

void Parameter::load()
{
    Serial.print("load Param... ");
    EEPROM.begin(512);
    EEPROM.get(0,lastAppIndex);
    EEPROM.get(1, param_ssid);
    EEPROM.get(1+sizeof(param_ssid), param_pass);
    char ok[2+1];
    EEPROM.get(1+sizeof(param_ssid)+sizeof(param_pass), ok);
    EEPROM.end();
    if (String(ok) != String("OK")) {
        //no Data in EEPROM --> load default
        param_ssid[0] = 0;
        param_pass[0] = 0;
        lastAppIndex = 0;
    }

    Serial.println("[OK]");
}

void Parameter::save()
{
    EEPROM.begin(512);
    EEPROM.put(0, lastAppIndex);
    EEPROM.put(1, param_ssid);
    EEPROM.put(1+sizeof(param_ssid), param_pass);
    char ok[2+1] = "OK";
    EEPROM.put(1+sizeof(param_ssid)+sizeof(param_pass), ok);
    EEPROM.commit();
    EEPROM.end();
}