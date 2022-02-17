#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
const char *ssid = "xiaowang";
const char *password = "xiaowang";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
ESP8266WebServer espServer(80);
void setup()
{
  Serial.begin(9600);
  delay(10);

  // prepare GPIO2
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  // server.begin();
  // Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
  // MDNS.begin ("esp8266");
  if (MDNS.begin("esp8266"))
  {
    Serial.println("MDNS responder started");
  }
  espServer.on("/", HTTP_GET, []()
               {
     String httpStr="<!DOCTYPE html><html><head><meta charset='UTF-8'></meta><title>esp8266 ADMIN</title></head><body><h2 align='center'>esp8266 WIFI CONFIG</h2><form method='POST'action='/config'><table align='center'><tr><td>SID:</td><td><input type='text' name='sid'></td></tr><tr><td>PASSWORD:</td><td><input type='text' name='password'></td></tr><tr><td><button type='submit'>Confirm</button></td></tr></table></form></body></html>";
              espServer.send(200,"text/html",httpStr); });
  espServer.on("/config", HTTP_POST, []()
               {
       Serial.println("receiver get");
                 if (espServer.hasArg("sid")){  
                   Serial.println(espServer.arg("sid"));                 
                 }
                 if (espServer.hasArg("password")){  
                   Serial.println(espServer.arg("password"));                 
                 }
                  espServer.send(200,"text/html","post ok");
                  });
  espServer.onNotFound([]()
                       { Serial.println("404"); });

  espServer.begin();
  Serial.println("Awesome! HTTP esp8266_server started!");
}

void loop()
{

  espServer.handleClient(); //检查有没有客户端设备通过网络向ESP8266网络服务器发送请求
  MDNS.update();

  // // Check if a client has connected
  // WiFiClient client = server.available();
  // if (!client) {
  //   return;
  // }

  // // Wait until the client sends some data
  // Serial.println("new client");
  // while(!client.available()){
  //   delay(1);
  // }

  // // Read the first line of the request
  // String req = client.readStringUntil('\r');
  // Serial.println(req);
  // Serial.println(req);
  // client.flush();

  // // Match the request
  // int val;
  // if (req.indexOf("/gpio/0") != -1)
  //   val = 0;
  // else if (req.indexOf("/gpio/1") != -1)
  //   val = 1;
  // else {
  //   Serial.println("invalid request");
  //   client.stop();
  //   return;
  // }

  // // Set GPIO2 according to the request
  // digitalWrite(LED_BUILTIN, val);

  // client.flush();

  // // Prepare the response
  // // String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  // // s += (val)?"high":"low";
  // // s += "</html>\n";

  // String s="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><head><meta charset='UTF-8'></meta><title>esp8266 ADMIN</title></head><body><h2 align='center'>esp8266 WIFI CONFIG</h2><form method='post'action='confirm'><table align='center'><tr><td>SID:</td><td><input type='text' name='sid'></td></tr><tr><td>PASSWORD:</td><td><input type='text' name='password'></td></tr><tr><td><button name='powerOff'type='submit'>Confirm</button></td></tr></table></form></body></html>";

  // // Send the response to the client
  // client.print(s);
  // delay(1);
  // Serial.println("Client disonnected");

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}