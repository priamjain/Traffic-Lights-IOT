char rd_light_pd;
char gr_light_pd;
char rd_light_tr;
char gr_light_tr;
int led = 2;

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "hpts";
const char *pass = "1236699qwerty"; 

unsigned int localPort = 2000; // local port to listen for UDP packets

IPAddress SendIP(192,168,43,255); //UDP Broadcast IP data sent to all devicess on same network

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

char packetBuffer[9];   
void setup()
{
  WiFi.mode(WIFI_STA);
  pinMode(led,OUTPUT);
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
    char a = packetBuffer[0];
    Serial.println(a);
    lights(a);
    
    
}
}

void lights(char a)
{
  if (a=='o')
  {
    digitalWrite(led,HIGH);
    
  }
  else if(a=='f')
  {
    digitalWrite(led,LOW);
  }
}
