#include <ArduinoJson.h>

String gr_light_tr;
String rd_light_tr;
String gr_light_pd;
String rd_light_pd;
String str;
const String ID = "Node Wifi";
const String Password = "make@banaao";

#include <ESP8266WiFi.h>;
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ID, Password); 
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
HTTPClient http;  //Declare an object of class HTTPClient
 
http.begin("http://jsonplaceholder.typicode.com/users/1");  //Specify request destination
int httpCode = http.GET();                                                                  //Send the request
 
if (httpCode > 0) { //Check the returning code
 
str = http.getString();   //Get the request response payload
Serial.println(str);                     //Print the response payload
 
}
 
http.end();   //Close connection
 
}
 
  padestrian(str); 
}


void padestrian(String rd_light_tr)
{
 if(rd_light_tr=='1')
 {
  delay(1000);
  gr_light_pd='1';
  //digitalWrite(gr_light_pd,HIGH);
  rd_light_pd='0' ;
  //digitalWrite(rd_light_pd,LOW);
  gr_light_tr='1';
  //digitalWrite(gr_light_tr,HIGH);
  rd_light_tr='0' ;
  //digitalWrite(rd_light_tr,LOW);
  //server.send(200, "text/html", rd_light_tr); 
 }
 if(rd_light_tr=='0')
 {
  delay(1000)
  gr_light_pd='0';
  //digitalWrite(gr_light_pd,LOW);
  rd_light_pd='1' ;
  //digitalWrite(rd_light_pd,HIGH);
  gr_light_tr='0';
  //digitalWrite(gr_light_tr,LOW);
  rd_light_tr='1' ;
  //digitalWrite(rd_light_tr,HIGH);
//   server.send(200, "text/html", rd_light_tr); 
 }
}
