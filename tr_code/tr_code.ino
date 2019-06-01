
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "hpts";
const char *pass = "1236699qwerty"; 
char p ;
unsigned int localPort = 2000; 
int flag=0;
IPAddress SendIP(192,168,43,255); 

WiFiUDP udp;

char packetBuffer[9];   
void setup()
{
  WiFi.mode(WIFI_STA);
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

void loop()
{
    if(flag==0)
    {
      p='f';
      udp.beginPacket(SendIP, 2000); 
        
        udp.write(p); 
        udp.endPacket();
        Serial.println(p);
        delay(3000);
       flag=1;
    }
    if (flag==1) 
    {
      p='o';
        udp.beginPacket(SendIP, 2000);
        
        udp.write(p);
        udp.endPacket();
        Serial.println(p);
        delay(3000);
        flag=0;
    }
}
