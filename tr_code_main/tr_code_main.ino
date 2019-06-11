
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
unsigned long time_now = 0;
const char *ssid = "hpts";
const char *pass = "1234567qwerty"; 
char p ;
char o;
unsigned int localPort = 2000; 
int flag=0;
int red_light=16;
int green_light=5;
char incomingPacket[255];
IPAddress SendIP(192,168,43,255); 

WiFiUDP udp;
void function()
{
  if (p=='R')
  {
    digitalWrite(red_light,HIGH);
    digitalWrite(green_light,LOW);
  }
  else if (p=='G')
  {
    digitalWrite(red_light,LOW);
    digitalWrite(green_light,HIGH);
  }
}
char packetBuffer[9];   
void setup()
{
  pinMode(green_light,OUTPUT);
  pinMode(red_light,OUTPUT);
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
   
    Serial.print("Local port: ");
    Serial.println(udp.localPort());
}

void loop()
{
   udp.begin(localPort);
      p='G';
      udp.beginPacket(SendIP, 2000); 
        
        udp.write(p); 
        udp.endPacket();
        Serial.println(p);
        function();
        time_now = millis();
   
    while(millis() < time_now + 10000){
      int packetSize = udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    o = packetBuffer[0];
  }
        
    }
    if(o=='I')
    {
      udp.beginPacket(SendIP,2000);
      udp.write("Q");
      udp.endPacket();
      digitalWrite(red_light,LOW);
      int i;
      for(i=0;i<5;i++)
      {
        digitalWrite(green_light,HIGH);
        delay(1000);
        digitalWrite(green_light,LOW);
        delay(1000);
        
      }
      p='R';
       udp.beginPacket(SendIP, 2000); 
        
        udp.write(p); 
        udp.endPacket();
        Serial.println(p);
        function();
        delay(30000);
      udp.beginPacket(SendIP,2000);
      udp.write("W");
      udp.endPacket();
      digitalWrite(green_light,LOW);
      for(i=0;i<5;i++)
      {
        digitalWrite(red_light,HIGH);
        delay(1000);
        digitalWrite(red_light,LOW);
        delay(1000);
        
      }
        
    }
    o='N';
    }
    /*
    else if (flag==1) 
   {
      p='G';
        udp.beginPacket(SendIP, 2000);
        
        udp.write(p);
        udp.endPacket();
        Serial.println(p);
        function();
         time_now = millis();
        while(millis() < time_now + 40000){
  int packetSize = udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    char o = packetBuffer[0];
    
  }
  if (o=='I')
  {
    
  }
        flag=0;
    }
    
}
}
*/
