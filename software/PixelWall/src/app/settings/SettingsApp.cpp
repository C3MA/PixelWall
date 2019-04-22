#include "SettingsApp.h"

#ifdef ARDUINO
#include "../../Parameter.h"
#else
#include <ParameterGUI.h>
#endif

SettingsApp::SettingsApp(LedPanel* panelPnt)
{
    panel = panelPnt;
}

void SettingsApp::start()
{
	panel->clear();
	panel->printImage(panel->letters.s, 0, 2, RGBColor(255, 255, 255), true, 0);
	panel->printImage(panel->letters.e, 4, 2, RGBColor(255, 255, 255), true, 0);
	panel->printImage(panel->letters.t, 8, 2, RGBColor(255, 255, 255), true, 0);
	panel->show();
}

void SettingsApp::end()
{

}


void SettingsApp::loop()
{

}

void SettingsApp::newWebsocketData(uint8_t * payload, size_t lenght)
{
	
}

WebsiteResponse_t SettingsApp::getWebsiteResponse(String parameter)
{
	

	WebsiteResponse_t response;


#ifdef ARDUINO

	if (parameter != "")
	{
		int begin = parameter.indexOf("=")+1;
		int end = parameter.indexOf("&");
		String ssid = parameter.substring(begin, end);
		String pass = parameter.substring(end + 6);
		ssid.toCharArray(Parameter::param_ssid, 50);
		pass.toCharArray(Parameter::param_pass, 50);

		Parameter::save();
	}

	response.statusCode = 200;
	response.header1 = WebSites::HTMLHeader1;
	strcpy(response.title, "Settings");
	response.header2 = WebSites::HTMLHeader2;
	String body = WebSites::getContentSettings(Parameter::param_ssid, Parameter::param_pass);
	body.toCharArray(websiteBuffer, 500);
	response.body = websiteBuffer;
#else

	if (parameter != "")
	{
		array<String>^ strValues = parameter->Split('&');
		Parameter::param_ssid = strValues[0]->Substring(strValues[0]->IndexOf("=") + 1);
		Parameter::param_pass = strValues[1]->Substring(strValues[1]->IndexOf("=") + 1);
		Parameter::save();
	}

	String body = WebSites::getContentSettings(Parameter::param_ssid, Parameter::param_pass);
	IntPtr ptrToNativeString = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(body);
	char* nativeString = static_cast<char*>(ptrToNativeString.ToPointer());
	response.body = nativeString;

#endif

	return response;
}

void SettingsApp::buttonEvent(Buttons::ButtonEvent_t btnEvent)
{

}

void SettingsApp::timerTick()
{

}

String SettingsApp::getName()
{
    return "settings";
}