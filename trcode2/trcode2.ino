int red_light=16;
int green_light=5;
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>;

const char *ssid = "Traffic Light wifi";
const char *pass = "$AqdbJK*%ElCa%#yXVUubLc595Jx@E4MP99dkxsRuff!ejkHCd"; 
char p;
unsigned int localPort = 2000; // local port to listen for UDP packets

IPAddress SendIP(192,168,43,255); //UDP Broadcast IP data sent to all devicess on same network

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

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
    udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(udp.localPort());
}

void loop()
{
    
      
  int packetSize = udp.parsePacket();
  if(packetSize)
  {
    udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    p = packetBuffer[0];
    Serial.println(p);
    function();
    
    
}
}

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
