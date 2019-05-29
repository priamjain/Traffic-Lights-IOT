/*
    Wireless Serial using UDP ESP8266
    Hardware: NodeMCU
    Circuits4you.com
    2018
    Slave Board connects to Access Point
*/
char rd_light_pd;
char gr_light_pd;
char rd_light_tr;
char gr_light_tr;
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "Node";
const char *pass = "test123"; 
char *var2;
unsigned int localPort = 2000; // local port to listen for UDP packets

IPAddress ServerIP(192,168,4,1);
IPAddress ClientIP(192,168,4,2);

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

char packetBuffer[9];   //Where we get the UDP data
//======================================================================
//                Setup
//======================================================================
void setup()
{
    Serial.begin(9600);
    Serial.println();

    WiFi.begin(ssid, pass);   //Connect to access point
  
    Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
    
    //Start UDP
    Serial.println("Starting UDP");
    udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(udp.localPort());
}
//======================================================================
//                MAIN LOOP
//======================================================================
void loop()
{
    int cb = udp.parsePacket();
    if (!cb) 
    {
      //If serial data is recived send it to UDP
           // We've received a UDP packet, send it to serial
      udp.read(packetBuffer, 1); // read the packet into the buffer, we are reading only one byte
      var2=packetBuffer;
      Serial.print("Before:");
      Serial.println(var2);
      padestrian(var2[0]);
      
      Serial.print("After:");
      Serial.println(var2);
        udp.beginPacket(ServerIP, 2000);  //Send Data to Master unit
        //Send UDP requests are to port 2000
        
        char a[1];
        a[0]=rd_light_tr; //Serial Byte Read
        udp.write(a,1); //Send one byte to ESP8266 
        udp.endPacket();
        
    }
}
//=======================================================================


void padestrian(char rd_light_tr)
{
 if(rd_light_tr=='1')
 {
  delay(10000);
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
  delay(10000);
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
