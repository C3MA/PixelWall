#include "webSites.h"

const char WebSites::HTMLHeader1[] = "<!DOCTYPE html>"
    "<html><head>"
    "<meta charset=\"utf-8\">"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\">"
    "<link href=\"http://enelsoft.de/templates/enelsoft/favicon.ico\" rel=\"shortcut icon\" type=\"image/x-icon\" />"
    "<title>PixelWall</title>"
    "<style>"
    "body{margin:0px;background-color:#303030;color:#D4D4D4;}"
    ".panelRow{"
    "display: inline-block;"
    "font-size: 0;"
    "margin-top: 1px;}"
    ".pixel{"
    "float: left;"
    "width: 20px;"
    "height: 20px;"
    "margin-right:1px;"
    "background-color: #000;"
    "}"
    "a{text-decoration:none;color:#D4D4D4;}"
    "input{height:35px;font-size:30px;background-color: #111;color:#D4D4D4;border:solid 1px #D4D4D4;}"
    ".title{width:100%;height: 50px;background-color: #001EC8;text-align: center;font-size:35px;color:#fff;}"
    ".navBack{float: left;width: 50px;border-right: solid 1px #11f;text-decoration: none;color:#fff;}"
    ".navIcon{float:right;width: 50px;height: 50px;border-left: solid 1px #11f;}"
    ".tetrisButton{box-sizing: border-box;background-color: #ccc;float: left;height:120px;padding: 5px;border: solid 5px white;font-size: 80px;text-align: center;cursor: default;}"
    ".button{box-sizing: border-box;color:#D4D4D4;background: linear-gradient(10deg, #000, #3B3B3B);height:100px;margin: 1%;line-height: 100px;display:inline-block;width: 300px;border-radius:8px;border:solid 2px #5b5b5b;font-size: 30px;font-weight: bold;text-align:center;cursor:pointer;}"
    ".unselectable{-webkit-user-select: none; /* Safari */-moz-user-select: none; /* Firefox */-ms-user-select: none; /* IE10+/Edge */user-select: none; /* Standard */}"
    ".content{width:100%;max-width:720px;margin: auto;text-align:center;}"
    "</style>"
	"<script type=\"text/javascript\">"
	"var connection;"
	"setTimeout(openWebSocket, 500);\r\n"
	"var cir;"
	"function openWebSocket(){"
	"cir = document.getElementById('conCircle');\r\n"
	"connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);"
	"connection.onopen = function () {"
	"console.log('connected');"
	"cir.style.fill=\"#3d3\";"
	"};"
	"connection.onerror = function (error) {"
	"console.log('WebSocket Error ', error);"
	"cir.style.fill=\"#3dd\";"
	"};"
	"connection.onmessage = function (e) {\n\r"
	"console.log('Server: ', e.data);\n\r"
	"if(typeof(wsData)!=\"undefined\"){wsData(e.data);}"
	"};\n\r"
	"connection.onclose = function () {"
	"console.log('WebSocket connection closed');"
	"cir.style.fill=\"#d33\";"
	"};"
	"}"
	"function send(data){"
	"connection.send(data);"
	"}"
	"</script>"
    "</head>"
    "<body>"
    "<div class=\"title\">"
    "<a href=\"./\" class=\"navBack\">&#8678</a>";

const char WebSites::HTMLHeader1NoWs[] = "<!DOCTYPE html>"
"<html><head>"
"<meta charset=\"utf-8\">"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\">"
"<link href=\"http://enelsoft.de/templates/enelsoft/favicon.ico\" rel=\"shortcut icon\" type=\"image/x-icon\" />"
"<title>PixelWall</title>"
"<style>"
"body{margin:0px;background-color:#303030;color:#D4D4D4;}"
".panelRow{"
"display: inline-block;"
"font-size: 0;"
"margin-top: 1px;}"
".pixel{"
"float: left;"
"width: 20px;"
"height: 20px;"
"margin-right:1px;"
"background-color: #000;"
"}"
"a{text-decoration:none;color:#D4D4D4;}"
"input{height:35px;font-size:30px;background-color: #111;color:#D4D4D4;border:solid 1px #D4D4D4;}"
".title{width:100%;height: 50px;background-color: #001EC8;text-align: center;font-size:35px;color:#fff;}"
".navBack{float: left;width: 50px;border-right: solid 1px #11f;text-decoration: none;color:#fff;}"
".navIcon{float:right;width: 50px;height: 50px;border-left: solid 1px #11f;}"
".tetrisButton{box-sizing: border-box;background-color: #ccc;float: left;height:120px;padding: 5px;border: solid 5px white;font-size: 80px;text-align: center;cursor: default;}"
".button{box-sizing: border-box;color:#D4D4D4;background: linear-gradient(10deg, #000, #3B3B3B);height:100px;margin: 1%;line-height: 100px;display:inline-block;width: 300px;border-radius:8px;border:solid 2px #5b5b5b;font-size: 30px;font-weight: bold;text-align:center;cursor:pointer;}"
".unselectable{-webkit-user-select: none; /* Safari */-moz-user-select: none; /* Firefox */-ms-user-select: none; /* IE10+/Edge */user-select: none; /* Standard */}"
".content{width:100%;max-width:720px;margin: auto;text-align:center;}"
"</style>"
"</head>"
"<body>"
"<div class=\"title\">"
"<a href=\"./\" class=\"navBack\">&#8678</a>";


const char WebSites::HTMLHeader2[] = "<div class=\"navIcon\"><svg height=\"50\" width=\"50\">"
    "<circle id=\"conCircle\" cx=\"25\" cy=\"25\" r=\"15\" fill=\"red\" onclick=\"openWebSocket()\" />"
    "</svg></div></div>";

const char WebSites::HTMLHeader2NoWs[] = "<div class=\"navIcon\"></div></div>";


const char WebSites::HTMLPixelIt[] =  "<div class=\"content\">"
    "<div class=\"button unselectable\" style=\"width: 40%; height: 40px; font-size: 20px; line-height:40px;\" onmousedown=\"clearAll()\">clear</div>"
    "<select id=\"colorSelector\" class=\"button\" style=\"width: 40%; height: 40px; font-size: 20px; background-color:#303030; \" onchange=\"selectColor()\">"
    "<option selected>white</option>"
    "<option>red</option>"
    "<option>green</option>"
    "<option>blue</option>"
    "<option>yellow</option>"
    "</select>"
    "</div>"
    "<div id=\"pixelGUI\" class=\"content\"></div>"
    "<script type=\"text/javascript\">"
    "setTimeout(creatGUI, 500);\r\n"
    "var r=255, g=255, b=255;"
    "var lastPixel = {\"x\":-1, \"y\":-1};"
    "var isTouch = (('ontouchstart' in window) || (navigator.msMaxTouchPoints > 0));"
    "var hoverDraw = false;\r\n"
    "function creatGUI(){\r\n"
    "var pixelGUI = document.getElementById(\"pixelGUI\");\r\n"
    "pixelGUI.innerHTML = \"\";\r\n"
    "for(let y = 0; y < 18; y++){"
    "var row = document.createElement('div');"
    "row.className = \"panelRow\";"
    "for(let x = 0; x < 12; x++){"
    "var p = document.createElement('div');"
    "p.className = \"pixel\";"
    "p.id=\"p\"+x+\"_\"+y;"
    "if(isTouch){"
    "p.addEventListener('touchstart', function(){setPixel(x,y);hoverDraw=true;}, false);"
    "p.addEventListener('touchend', function(){hoverDraw=false;}, false);"
    "p.addEventListener('touchmove', function(){setPixel(x,y);}, false);"    
    "}else{"
    "p.addEventListener('mousedown', function(){setPixel(x,y);hoverDraw=true;}, false);"
    "p.addEventListener('mouseup', function(){hoverDraw=false;}, false);"
    "p.addEventListener('mousemove', function(){if(hoverDraw==true){setPixel(x,y);}}, false);"
    "}\r\n"
    "row.appendChild(p);"
    "}\r\n"
    "pixelGUI.appendChild(row);\r\n"
    "pixelGUI.appendChild(document.createElement('br'));\r\n"
    "}"
    "}"
    "function setPixel(x, y){\r\n"
    "if(lastPixel[\"x\"]==x && lastPixel[\"y\"]==y){return;}\r\n"
    "lastPixel = {\"x\":x, \"y\":y};"
    "send(x+\",\" + y + \",\"+r+\",\"+g+\",\"+b);"
    "document.getElementById(\"p\"+x+\"_\"+y).style.backgroundColor=\"rgb(\"+r+\",\"+g+\",\"+b+\")\";"
    "}"
	"function clearAll(){\r\n"
	"for(let y = 0; y < 18; y++){"
	"for(let x = 0; x < 12; x++){"
	"document.getElementById(\"p\"+x+\"_\"+y).style.backgroundColor=\"rgb(0,0,0)\";"
	"}}"
	"send('c');"
	"}"
    "function selectColor(){"
    "var sColor = document.getElementById(\"colorSelector\").value;"
    "if(sColor==\"white\"){r=255;g=255;b=255;}\r\n"
    "if(sColor==\"red\"){r=255;g=0;b=0;}\r\n"
    "if(sColor==\"green\"){r=0;g=255;b=0;}\r\n"
    "if(sColor==\"blue\"){r=0;g=0;b=255;}\r\n"
    "if(sColor==\"yellow\"){r=255;g=255;b=0;}\r\n"
    "}"
    "</script>"
    "</body></html>";

const char WebSites::HTMLTetris[] = "<div class=\"content\">"
"<div id=\"score\" style=\"width: 100%; text-align: center; font-weight: bold; font-size: 20px;\">Score: </div>"
"<div class=\"button unselectable\" style=\"width: 26%; font-size: 80px;\" onmousedown=\"send('l')\">&lt;</div>"
"<div class=\"button unselectable\" style=\"width:42%; font-size: 80px;\" onmousedown=\"send('t')\">&orarr;</div>"
"<div class=\"button unselectable\" style=\"width: 26%; font-size: 80px;\" onmousedown=\"send('r')\">&gt;</div><br />"
"<div class=\"button unselectable\" style=\"width:48%; font-size: 80px;\" onmousedown=\"send('d')\" onmouseup=\"send('n')\">&#8675;</div>"
"<div class=\"button unselectable\" style=\"width:48%; font-size: 80px;\" onmousedown=\"send('d')\">&#8609;</div>"
"<div class=\"button unselectable\" style=\"width:38%; font-size: 80px;\" onmousedown=\"send('p')\">P</div>"
"</div>"
"<script>"
"function wsData(data){"
"document.getElementById('score').innerHTML=\"Score: \"+data"
"}"
"</script>"
"</body></html>";

const char WebSites::HTMLSnake[] = "<div class=\"content\">"
"<div id=\"score\" style=\"width: 100%; text-align: center; font-weight: bold; font-size: 20px;\">Score: </div>"
"<div class=\"button unselectable\" style=\"width:48%; font-size: 80px;\" onmousedown=\"send('u')\">hoch</div><br />"
"<div class=\"button unselectable\" style=\"width: 26%; font-size: 80px;\" onmousedown=\"send('l')\">&lt;</div>"
"<div class=\"button unselectable\" style=\"width: 26%; font-size: 80px;\" onmousedown=\"send('r')\">&gt;</div><br />"
"<div class=\"button unselectable\" style=\"width:48%; font-size: 80px;\" onmousedown=\"send('d')\">runter</div><br />"
"<div class=\"button unselectable\" style=\"width:38%; font-size: 80px;\" onmousedown=\"send('p')\">pause/play</div>"
"</div>"
"<script>"
"function wsData(data){"
"document.getElementById('score').innerHTML=\"Score: \"+data"
"}"
"</script>"
"</body></html>";

const char WebSites::empty[] = "";

const char WebSites::HTMLError404[] = "<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>";

const char WebSites::HTMLDefault[] =  "<div class=\"content\">"
"<a class=\"button\" href=\"/settings\">settings</a>"
"<a class=\"button\" href=\"/clock\">clock</a><br />"
"<a class=\"button\" href=\"/tetris\">tetris</a>"
"<a class=\"button\" href=\"/spaceInvaders\">Space Invaders</a><br />"
"<a class=\"button\" href=\"/snake\">snake</a>"
"<a class=\"button\" href=\"/pixelIt\">pixel it!</a><br />"
"<a class=\"button\" href=\"/images\">show an image</a>"
"</div>"
"</body></html>";

const char WebSites::HTMLImages[] = "<div class=\"content\">"
"<b>Select mode:</b><br />"
"<select selected=\"selected\" class=\"button\" style=\"width: 40%; font-size: 20px; background-color:#303030; \" id=\"modeSelect\" onchange=\"send(this.value);if(this.value=='m2' || this.value=='m3'){document.getElementById('nextButton').style.display='inline-block';}else{document.getElementById('nextButton').style.display='none';}\">"
"<option value=\"m0\">dynamic rainbow</option>"
"<option value=\"m1\">dynamic single color</option>"
"<option value=\"m2\">static color</option>"
"<option value=\"m3\">static random</option></select>"
"<div id=\"nextButton\" class=\"button unselectable\" onmousedown=\"send('nx')\" style=\"width: 20%; font-size: 20px; display:none;\" >next</div><br />"
"<div id=\"s1Button\" class=\"button unselectable\" onmousedown=\"send('s1')\" style=\"width: 20%; font-size: 20px;\" >slow</div>"
"<div id=\"s2Button\" class=\"button unselectable\" onmousedown=\"send('s2')\" style=\"width: 20%; font-size: 20px;\" >middle</div>"
"<div id=\"s3Button\" class=\"button unselectable\" onmousedown=\"send('s3')\" style=\"width: 20%; font-size: 20px;\" >fast</div><br />"
"</div>"
"</body></html>";

const char WebSites::HTMLClock[] = "<div class=\"content\">"
"<div class=\"button unselectable\" style=\"width:38%; font-size: 30px;\" onmousedown=\"send('0')\">Mode 0</div>"
"<div class=\"button unselectable\" style=\"width:38%; font-size: 30px;\" onmousedown=\"send('1')\">Mode 1</div>"
"</div>"
"</body></html>";

const char WebSites::HTMLSpaceInvaders[] = "<div class=\"content\">"
"<div id=\"score\" style=\"width: 100%; text-align: center; font-weight: bold; font-size: 20px;\">Score: </div>"
"<div id=\"fireButton\" class=\"button unselectable\" style=\"width:90%; font-size: 80px;\">&#x21e1;</div><br /><br />"
"<div id=\"mlButton\" class=\"button unselectable\" style=\"width:30%; font-size: 80px;\">&lt;</div>"
"<div id=\"mrButton\" class=\"button unselectable\" style=\"width:30%; font-size: 80px;\">&gt;</div><br />"
"<div id=\"moveButton\" class=\"button unselectable\" style=\"width:90%; font-size: 80px;\">move</div>"
"<div id=\"restartButton\" class=\"button unselectable\" style=\"width:40%; font-size: 30px;\">restart</div>"
"</div>"
"<script type=\"text/javascript\">"
"var shipPos = 6, oldShipPos = 6;\r\n"
"var isTouch = (('ontouchstart' in window) || (navigator.msMaxTouchPoints > 0));"
"if(isTouch){"
"document.getElementById(\"moveButton\").addEventListener('touchmove', function(e){ move(e, true); }, false);"
"document.getElementById(\"fireButton\").addEventListener('touchstart', function(e){ send('f'); }, false);"
"document.getElementById(\"mlButton\").style.display='none';"
"document.getElementById(\"mrButton\").style.display='none';"
"document.getElementById(\"restartButton\").addEventListener('touchstart', function(e){ send('x'); }, false);"
"}else{"
"document.getElementById(\"moveButton\").style.display='none';"
"document.getElementById(\"fireButton\").addEventListener('mousedown', function(e){ send('f'); }, false);"
"document.getElementById(\"mlButton\").addEventListener('mousedown', function(e){ send('l'); }, false);"
"document.getElementById(\"mrButton\").addEventListener('mousedown', function(e){ send('r'); }, false);"
"document.getElementById(\"restartButton\").addEventListener('mousedown', function(e){ send('x'); }, false);"
"}\r\n"
"setTimeout(refreshShipPos, 200);\r\n"
"function move(e, touch)\r\n"
"{"
"var but = document.getElementById(\"moveButton\").getBoundingClientRect();"
"var mouseLeft;"
"if(touch==true)\r\n"
"mouseLeft = e.changedTouches[0].clientX - but.left;\r\n"
"else\r\n"
"mouseLeft = e.clientX - but.left;\r\n"
"var col = Math.round((mouseLeft * 11) / but.width);\r\n"
"shipPos = col;"
"}"
"function refreshShipPos(){"
"if(shipPos != oldShipPos){\r\n"
"send('m' + shipPos);\r\n"
"oldShipPos = shipPos;}\r\n"
"setTimeout(refreshShipPos, 50);\r\n"
"}"
"</script>"
"</body></html>";

const WebsiteResponse_t WebSites::errorPage404 = { 404 , "" , "" , "" , "" };

String WebSites::getHeader404(int responseLength)
{
    String sHeader;

    sHeader  = "HTTP/1.1 404 Not found\r\n";
    sHeader += "Content-Length: ";
	#ifdef ARDUINO
		sHeader += String(responseLength);
	#else
		sHeader += responseLength.ToString();
	#endif
    sHeader += "\r\n";
    sHeader += "Content-Type: text/html\r\n";
    sHeader += "Connection: close\r\n";
    sHeader += "\r\n";

    return sHeader;
}

String WebSites::getHeader200(int responseLength, String contentType)
{
    String sHeader;

    sHeader  = "HTTP/1.1 200 OK\r\n";
    sHeader += "Content-Length: ";
	#ifdef ARDUINO
		sHeader += String(responseLength);
	#else
		sHeader += responseLength.ToString();
	#endif
    sHeader += "\r\n";
    sHeader += "Content-Type: "+contentType+"\r\n";
    sHeader += "Connection: close\r\n";
    sHeader += "\r\n";

    return sHeader;
}

String WebSites::getContentSettings(String ssid, String pass)
{
	String content;

	content += "<div class=\"content\"><form action=\"settings\" method=\"GET\">";
	content += "WLAN SSID:<br />";
	content += "<input type=\"text\" name=\"ssid\" value=\""+ ssid+"\"/><br /><br />";
	content += "Password:<br />";
	content += "<input type=\"password\" name=\"pass\" value=\"" + pass + "\"/><br /><br />";
	content += "<div class=\"button\" style=\"width:40%\" onclick=\"document.querySelector('form').submit()\">save</div>";
	content += "</form></div>";
	content += "</body></html>";

	return content;
}