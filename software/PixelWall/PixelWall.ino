#include <Arduino.h>
#include <ESP8266WiFi.h>

//#include <GetInTouch.h>

#include "Buttons.h"
#include "src/Parameter.h"
#include "src/LedPanel.h"
#include "src/web/webserver.h"

#include "src/app/IPixelApp.h"
#include "src/app/default/DefaultApp.h"
#include "src/app/images/ImagesApp.h"
#include "src/app/pixelIt/PixelItApp.h"
#include "src/app/clock/ClockApp.h"
#include "src/app/tetris/TetrisApp.h"
#include "src/app/settings/SettingsApp.h"
#include "src/app/spaceInvaders/SpaceInvadersApp.h"
#include "src/app/snake/SnakeApp.h"

//GetInTouch git;
//GITAction ledMatrix("draw a pixel image");

void showOnMatrix(String data);
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t lenght);
WebsiteResponse_t webServerRequest(String request, String parameter);
void sendWebsocketData(char* payload, uint8_t len);
void ICACHE_RAM_ATTR onTimerISR();

Buttons buttons;
Buttons::ButtonEvent_t buttonState;
LedPanel panel;
WebSites webSites;
Parameter parameter;
WebServer webserver(webSocketEvent, webServerRequest);
DefaultApp defaultApp(&panel);
SettingsApp settingsApp(&panel);
ImagesApp imagesApp(&panel);
PixelItApp pixelItApp(&panel, sendWebsocketData);
ClockApp clockApp(&panel);
TetrisApp tetrisApp(&panel, sendWebsocketData);
SpaceInvadersApp spaceInvadersApp(&panel, sendWebsocketData);
SnakeApp snakeApp(&panel, sendWebsocketData);
int oldADCValue = 0;
int ADCCounter = 0;

#define NUM_OF_APPS 8
IPixelApp *currApp;
IPixelApp* allApps[NUM_OF_APPS] = {&defaultApp, &settingsApp, &imagesApp, &pixelItApp, &clockApp, &tetrisApp, &spaceInvadersApp, &snakeApp};

void setup()
{
  panel.clear(0);
  panel.clear(1);

  buttons.init();
  panel.ledMatrix.setBrightness(20);

  Parameter::load();

  currApp = allApps[Parameter::lastAppIndex];
  Serial.begin(115200);
  //Serial.begin(9600);
  
  delay(2000);

  Serial.println("ESP8266");
  Serial.println("Pixel Wall [by enny]");

  // inital connect
  defaultApp.setDisplayMode(DefaultApp::displayMode_t::SEARCH_WLAN);

  if(!ConnectToWLAN())
  {
    //we got no WiFi connection
    defaultApp.setDisplayMode(DefaultApp::displayMode_t::NO_WIFI);
    Serial.print("set mode AP...");
    WiFi.mode(WIFI_AP);
    Serial.println(" [OK]");
    Serial.print("start softAP...");
    WiFi.softAP("pixelWall", "");
    Serial.println(" [OK]");

    Serial.print("My IP is: ");
    Serial.println(WiFi.softAPIP());
  }
  else
  {
    defaultApp.setDisplayMode(DefaultApp::displayMode_t::SHOW_IP);
    IPAddress addr = WiFi.localIP();
    defaultApp.setIP(addr[0], addr[1], addr[2], addr[3]);
  }

  Serial.print("start Webserver...");
  webserver.start();
  Serial.println(" [OK]");

  delay(500);

  //Initialize Ticker every 10ms
  timer1_attachInterrupt(onTimerISR);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
  timer1_write(50000); //10ms (80MHz/16 * 0,01s)

  currApp->start();

  //ledMatrix.addPixelMatrix("matrix", 12, 18);
  //git.init();
  //git.addAction(&ledMatrix);
}

void ICACHE_RAM_ATTR onTimerISR(){
  currApp->timerTick();
}

bool ConnectToWLAN()
{
  unsigned int timeout = 20; //20*500ms = 10s Timeout for connection
  // Connect to WiFi network
  Serial.println();
  Serial.print("=== Try to connect to ");
  Serial.print(Parameter::param_ssid);
  Serial.println(" ===");

  Serial.print("Disconnect ESP... ");
  WiFi.disconnect();
  Serial.println(" [OK]");
  Serial.print("Set mode STA... ");
  WiFi.mode(WIFI_STA);
  Serial.println(" [OK]");
  Serial.print("Connect");
  WiFi.begin(Parameter::param_ssid, Parameter::param_pass);

  while (WiFi.status() != WL_CONNECTED && timeout!=0)
  {
    for(int i = 0; i < 50; i++)
    {
      delay(10);
      defaultApp.timerTick();
      defaultApp.loop();
    }
    Serial.print(".");
    timeout--;
  }

  if(timeout!=0)
  {
    Serial.println("WiFi connected!");
    Serial.print("My IP is: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("could not connect to WiFi.");
    WiFi.disconnect();
  }

  return timeout!=0;
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{ // When a WebSocket message is received
  Serial.println("ws Event! (len: " + String(length) + " | " + String(type) + ")");

  switch (type)
  {
  case WStype_DISCONNECTED: // if the websocket is disconnected
    Serial.printf("[%u] Disconnected!\n", num);
    break;
  case WStype_CONNECTED:
    Serial.printf("[%u] Connected", num);
    break;
  case WStype_TEXT: // if new text data is received
    //Serial.printf("[%u] get Text: %s\n", num, payload);
    currApp->newWebsocketData(payload, length);
    break;
  case WStype_BIN:
    currApp->newWebsocketData(payload, length);
    break;
  }

}

WebsiteResponse_t webServerRequest(String request, String parameter)
{
  for(unsigned int i = 0; i < NUM_OF_APPS; i++)
  {
    if(allApps[i]->getName() == request)
    {
      if(currApp != allApps[i])
      {
        currApp->end();
        currApp = allApps[i];
        currApp->start();
        Parameter::lastAppIndex = i;
        Parameter::save();
      }
      return currApp->getWebsiteResponse(parameter);
    }
  }

  return WebSites::errorPage404;
}

void sendWebsocketData(char* payload, uint8_t len)
{
  webserver.sendData(payload, len);
}

void loop()
{

  webserver.loop();
  
  Buttons::ButtonEvent_t buttonState = buttons.getPressedButton();

  if(buttonState.button != Buttons::Button_t::NONE)
  {
    if(buttonState.button == Buttons::Button_t::NES_SELECT || buttonState.button == Buttons::Button_t::APP_SELECT)
    {
      if(buttonState.event == Buttons::Event_t::DOWN)
      {
        Parameter::lastAppIndex++;
        if(Parameter::lastAppIndex >= NUM_OF_APPS)
          Parameter::lastAppIndex = 0;

        Parameter::save();
        currApp->end();
        currApp = allApps[Parameter::lastAppIndex];
        currApp->start();
      }
    }
    else
    {
      currApp->buttonEvent(buttonState);
    }
  }

  currApp->loop();
  
  if(buttons.buttonModulPresent())
  {
    if(ADCCounter++ > 100)
    {
      int tmp = analogRead(A0);
      if(tmp > oldADCValue + 5 || tmp < oldADCValue - 5)
      {
        oldADCValue = tmp;

        tmp = tmp / 10;
        if(tmp > 100) tmp = 100;
        if(tmp < 1) tmp = 1;
        panel.ledMatrix.setBrightness(tmp);
      }
      ADCCounter=0;
    }
  }
  else
  {
    ADCCounter=0;
  }


  /*git.run();

  if(ledMatrix.isTriggered()) {
      //show the user input
      showOnMatrix(ledMatrix.getParameter("matrix"));

      //tell the server that the action is now ended
      ledMatrix.ended();
  }*/
}


/*
void showOnMatrix(String data)
{
  for(uint8_t i = 0; i < data.length() && i < (panel.COLS * panel.ROWS); i++)
  {
    int col = i % panel.COLS;
    int row = i / panel.COLS;

    if(data.charAt(i)=='1')
      // red
      //neoPixels.setPixelColor(i, MATRIX_BRIGHTNESS,0,0);
      panel.setLed(col, row, RGBColor(255,0,0), 0);
    else if(data.charAt(i)=='2')
      // green
      //neoPixels.setPixelColor(i, 0, MATRIX_BRIGHTNESS,0);
      panel.setLed(col, row, RGBColor(0,255,0), 0);
    else if(data.charAt(i)=='3')
      // blue
      //neoPixels.setPixelColor(i, 0, 0, MATRIX_BRIGHTNESS);
      panel.setLed(col, row, RGBColor(0,0,255), 0);
    else if(data.charAt(i)=='4')
      // white
      //neoPixels.setPixelColor(i, MATRIX_BRIGHTNESS, MATRIX_BRIGHTNESS, MATRIX_BRIGHTNESS);
      panel.setLed(col, row, RGBColor(255,255,255), 0);
    else if(data.charAt(i)=='5')
      // yellow
      //neoPixels.setPixelColor(i, MATRIX_BRIGHTNESS, MATRIX_BRIGHTNESS, 0);
      panel.setLed(col, row, RGBColor(255,255,0), 0);
    else if(data.charAt(i)=='6')
      // orange
      //neoPixels.setPixelColor(i, MATRIX_BRIGHTNESS, (MATRIX_BRIGHTNESS >> 1), 0);
      panel.setLed(col, row, RGBColor(255,128,0), 0);
    else 
      // black
      //neoPixels.setPixelColor(i, 0, 0, 0);
      panel.setLed(col, row, RGBColor(0,0,0), 0);
  }
  
  panel.show();
}*/