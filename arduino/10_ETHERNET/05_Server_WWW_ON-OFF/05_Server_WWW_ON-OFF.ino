// MIX
// Arduino dla początkujących. Kolejny krok
// Zabawy z elektroniką. Ilustrowany przewodnik dla wynalazców i pasjonatów

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetServer server(80);
EthernetClient client;

int relayPin = 4;

char line1[110];
char buffer[110];

void setup()
{
  pinMode(relayPin, OUTPUT);
  Ethernet.begin(mac);
  server.begin();
  // Serial.begin(9600);
}

void loop()
{
  client = server.available();
  if (client) 
  {
    while (client.connected()) 
    {
      readHeader();
      digitalWrite(relayPin, valueOfParam('a'));
      client.println(F("HTTP/1.1 200 OK"));
      client.println(F("Content-Type: text/html"));
      client.println();
      client.println(F("<html><body>"));
      client.println(F("<h1>Zdalny przekaznik</h1>"));
      client.println(F("<h2><a href='?a=1'/>Wlaczony</a></h2>"));
      client.println(F("<h2><a href='?a=0'/>Wylaczony</a></h2>"));
      client.println(F("</body></html>"));
      client.stop();            
    }
  }
}

void readHeader()   // W efekcie zapełnia tablicę line1 nagłówkiem wiadomości (patrz 'line1 = ' niżej)
{
  readRequestLine(line1);
  while (readRequestLine(buffer) > 1 && buffer[0] != '\n')  {  }
}

int readRequestLine(char *line)
{
  char ch;
  int i = 0;
  while (ch != '\n' && i < 100 && client.available())
  {
    if (client.available())
    {
      ch = client.read();
      line[i] = ch;
      i++;
    }
  }
  line[i] = '\0';
  return i;
}

int valueOfParam(char param)                      // param = a
{
  for (int i = 0; i < strlen(line1); i++)         // strlen(line1) = 16 / 20
  {
    if (line1[i] == param && line1[i+1] == '=')   // line1 = GET / HTTP/1.1    albo    GET /?a=1 HTTP/1.1
    {
      return (line1[i+2] - '0');
    }
  }
  return 0;
}