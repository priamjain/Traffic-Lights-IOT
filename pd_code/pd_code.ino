int red_light=16;
int green_light=5;
int button=4;
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>;

const char *ssid = "hpts";
const char *pass = "1234567qwerty";   
char p;
unsigned int localPort = 2000; // local port to listen for UDP packets

IPAddress SendIP(192,168,43,255); //UDP Broadcast IP data sent to all devicess on same network

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

char packetBuffer[9];   
void setup()
{ pinMode(button,OUTPUT);
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
   udp.begin(localPort); 
    //Start UDP
}

void loop()
{
  
  int temp =digitalRead(button);
  if(temp==HIGH)
  {
    Serial.println("I");
    udp.beginPacket(SendIP, 2000); 
        
        udp.write("I"); 
        udp.endPacket();
   }
   else
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
}

void function()
{
  if (p=='R')
  {
    digitalWrite(red_light,LOW);
    digitalWrite(green_light,HIGH);
  }
  else if (p=='G')
  {
    digitalWrite(red_light,HIGH);
    digitalWrite(green_light,LOW);
  }
  else if (p=='Q')
  {
    digitalWrite(green_light,LOW);
    int i;
    for(i=0;i<5;i++)
    {
    digitalWrite(red_light,HIGH);
    delay(1000);
    digitalWrite(red_light,LOW);
    delay(1000);
    }
  }
    else if (p=='W')
  {
    digitalWrite(red_light,LOW);
    int i;
    for(i=0;i<5;i++)
    {
    digitalWrite(green_light,HIGH);
    delay(1000);
    digitalWrite(green_light,LOW);
    delay(1000);
    }
  }
}
