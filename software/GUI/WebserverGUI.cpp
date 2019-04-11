#include "WebserverGUI.h"
#include "../src/web/webSites.h"

using namespace System::Runtime::InteropServices;
using namespace System::Text;
using namespace System::Text::RegularExpressions;
using namespace System::Net::WebSockets;

WebserverGUI::WebserverGUI(ResponseCallback^ callback, WebsocketDataCallback^ wsDataCb) :
	_responderMethod(callback),
	_wsDataMethod(wsDataCb),
	webSocketServer(81)
{
	webserverListener.Prefixes->Add("http://localhost:8080/");
	webserverListener.Start();
	webSocketServer.Start();
}

String WebserverGUI::webserverRequest(HttpListenerRequest^ request)
{
	String sPath = request->Url->LocalPath;
	String sParam = request->Url->Query;

	if (sPath->Length > 0)
		sPath = sPath->Substring(1);		//remove the first /

	if (sParam->Length > 0)
		sParam = sParam->Substring(1);		//remove the ? at the beginning

	/*if (request->IsWebSocketRequest)
	{
		sParam = "";
	}*/
	

	String sResponse;
	StringBuilder^ outputsb = gcnew StringBuilder();

	
	WebsiteResponse_t response = _responderMethod(sPath, sParam);
		
	//sResponse = Marshal::PtrToStringAnsi(IntPtr((char *)response.pageHeader));
	sResponse = Marshal::PtrToStringAnsi(IntPtr((char *)response.header1));
	sResponse += Marshal::PtrToStringAnsi(IntPtr((char *)response.title));
	sResponse += Marshal::PtrToStringAnsi(IntPtr((char *)response.header2));
	sResponse += Marshal::PtrToStringAnsi(IntPtr((char *)response.body));

	return sResponse;


}

void WebserverGUI::Run()
{
	wsThread->Start();
	webSocketThread->Start();
}

void WebserverGUI::RunThread()
{
	try
	{
		while (webserverListener.IsListening)
		{
			HttpListenerContext^ ctx;

			try
			{
				ctx = webserverListener.GetContext();
				String rstr = webserverRequest(ctx->Request);
				Encoding^ enc;
				array<unsigned char>^ buf = enc->UTF8->GetBytes(rstr);
				
				ctx->Response->ContentLength64 = buf->Length;
				ctx->Response->OutputStream->Write(buf, 0, buf->Length);
			}
			finally
			{
				// always close the stream
				ctx->Response->OutputStream->Close();
			}

			Thread::Sleep(50);
		}
	}
	finally{}
}

void WebserverGUI::Stop()
{
	webserverListener.Stop();
	webserverListener.Close();
}

void WebserverGUI::sendData(uint8_t* payload, uint8_t len)
{
	NetworkStream^ stream = client->GetStream();
	
	array<unsigned char>^ buffer = gcnew array<Byte>(len+2);
	
	buffer[0] = 129;
	buffer[1] = len;

	for (int i = 0; i < len; i++)
	{
		buffer[2+i] = payload[i];
	}

	stream->Write(buffer, 0, 2 + len);

}

void WebserverGUI::WebSocketRunThread()
{
	//quelle: https://developer.mozilla.org/en-US/docs/Web/API/WebSockets_API/Writing_WebSocket_server
	while (1)
	{
		client = webSocketServer.AcceptTcpClient();

		NetworkStream^ stream = client->GetStream();

		//enter to an infinite cycle to be able to handle every change in stream
		while (true) {
			while (!stream->DataAvailable);

			array<System::Byte>^ bytes = gcnew array<Byte>(client->Available);

			stream->Read(bytes, 0, bytes->Length);

			//translate bytes of request to string
			String data = Encoding::UTF8->GetString(bytes);

			if (Regex::IsMatch(data, "^GET")) {
				String eol = "\r\n"; // HTTP/1.1 defines the sequence CR LF as the end-of-line marker

				Regex^ reg = gcnew Regex("Sec-WebSocket-Key: (.*)");

				String response = "HTTP/1.1 101 Switching Protocols" + eol
					+ "Connection: Upgrade" + eol
					+ "Upgrade: websocket" + eol
					+ "Sec-WebSocket-Accept: " + Convert::ToBase64String(
						System::Security::Cryptography::SHA1::Create()->ComputeHash(
							Encoding::UTF8->GetBytes(
								reg->Match(data)->Groups[1]->Value->Trim() + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
							)
						)
					) + eol
					+ eol;


				array<Byte>^ responseArr = Encoding::UTF8->GetBytes(response);

				stream->Write(responseArr, 0, responseArr->Length);
			}
			else {
				if ((bytes[0] & 0xF) == 0x01)		//its a textmessage
				{
					unsigned char rxBuffer[1000];

					unsigned int len = bytes[1] & 0x7F;
					if (bytes[1] & 0x80)
					{
						//encoded data
						array< Byte >^ mask = { bytes[2], bytes[3], bytes[4], bytes[5] };

						for (unsigned int i = 0; i < len; i++) {
							rxBuffer[i] = (Byte)(bytes[i+6] ^ mask[i % 4]);
						}
					}
					else
					{
						//not encoded data
						for (int i = 0; i < data->Length; i++) {
							rxBuffer[i] = bytes[i + 2];
						}
					}

					//send received Data to app:
					_wsDataMethod(rxBuffer, len);

				}
				else if ((bytes[0] & 0xF) == 0x08)	//connection close frame
				{
					break;
				}
			}
		}

	}
}