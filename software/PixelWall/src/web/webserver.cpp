#include "webserver.h"

WebServer::WebServer(void (*webSocketCb)(uint8_t num, WStype_t type, uint8_t *payload, size_t length),WebsiteResponse_t (*webRequestCb)(String page, String parameter)) : 
    server(80),
    webSocket(81)
{
    wsCallback = webSocketCb;
    wrCallback = webRequestCb;
}

void WebServer::start()
{
    // Start the server
    server.begin();
    Serial.println("Server started");

    // Print the IP address
    Serial.println(WiFi.localIP());

    webSocket.begin();             // start the websocket server
    webSocket.onEvent(wsCallback); // if there's an incomming websocket message, go to function 'webSocketEvent'
    Serial.println("WebSocket server started.");
}
/*
void WebServer::sendDataString(String data)
{
    webSocket.broadcastTXT(data);
}
*/
void WebServer::sendData(char * payload, uint8_t length)
{
    webSocket.broadcastTXT((uint8_t*)payload, length);
}

void WebServer::loop()
{
    webSocket.loop();

    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)
    {
        return;
    }

    // Wait until the client sends some data
    Serial.println("new client");
    unsigned long ultimeout = millis() + 250;
    while (!client.available() && (millis() <= ultimeout))
    {
        delay(1);
    }
    if (millis() > ultimeout)
    {
        Serial.println("client connection time-out!");
        return;
    }

    // Read the first line of the request
    String sRequest = client.readStringUntil('\r');
    Serial.println(sRequest);
    client.flush();

    // stop client, if request is empty
    if (sRequest == "")
    {
        Serial.println("empty request! - stopping client");
        client.stop();
        return;
    }

    // get path; end of path is either space or ?
    // Syntax is e.g. GET /?pin=MOTOR1STOP HTTP/1.1
    String sPath = "", sParam = "", sCmd = "";
    String sGetstart = "GET ";
    int iStart, iEndSpace, iEndQuest;
    iStart = sRequest.indexOf(sGetstart);
    if (iStart >= 0)
    {
        iStart += +sGetstart.length();
        iEndSpace = sRequest.indexOf(" ", iStart);
        iEndQuest = sRequest.indexOf("?", iStart);

        // are there parameters?
        if (iEndSpace > 0)
        {
            if (iEndQuest > 0)
            {
                // there are parameters
                sPath = sRequest.substring(iStart+1, iEndQuest);
                sParam = sRequest.substring(iEndQuest + 1, iEndSpace);
            }
            else
            {
                // NO parameters
                sPath = sRequest.substring(iStart+1, iEndSpace);
            }
        }
    }

    Serial.println("PATH:" + sPath);
    Serial.println("PARAM:" + sParam);
    String sHeader, sResponse;
    WebsiteResponse_t response;

    response = wrCallback(sPath, sParam);

    if(response.statusCode == 404)
    {
        int length = strlen(WebSites::HTMLError404);
        client.print(WebSites::getHeader404(length));
        client.print(WebSites::HTMLError404);
    }
    else
    {
        int length = strlen(response.header1);
        length += strlen(response.title);
        length += strlen(response.header2);
        length += strlen(response.body);

        client.print(WebSites::getHeader200(length, "text/html"));
        client.print(response.header1);
        client.print(response.title);
        client.print(response.header2);
        client.print(response.body);
    }

    // and stop the client
    client.stop();
    Serial.println("Client disonnected");
}