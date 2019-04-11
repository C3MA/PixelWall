#pragma once

#include <gcroot.h>
#include <Arduino.h>
#include "../src/web/websites.h"

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;

ref class WebserverGUI
{
public:
	delegate String MyCallback(HttpListenerRequest^ request);
	delegate WebsiteResponse_t ResponseCallback(String request, String parameter);
	delegate void WebsocketDataCallback(uint8_t* payload, uint8_t length);
	WebserverGUI(ResponseCallback^ callback, WebsocketDataCallback^ wsDataCb);
	void Run();
	void Stop();
	void sendData(uint8_t* payload, uint8_t len);

private:
	String webserverRequest(HttpListenerRequest^ request);

	HttpListener webserverListener;
	TcpListener webSocketServer;
	TcpClient^ client;
	ResponseCallback^ _responderMethod;
	WebsocketDataCallback^ _wsDataMethod;
	
	void RunThread();
	void WebSocketRunThread();

	Thread ^ wsThread = gcnew Thread(gcnew ThreadStart(this, &WebserverGUI::RunThread));

	Thread ^ webSocketThread = gcnew Thread(gcnew ThreadStart(this, &WebserverGUI::WebSocketRunThread));

};

