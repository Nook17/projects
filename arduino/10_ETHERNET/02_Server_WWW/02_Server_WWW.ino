// 12_02_serwer - Arduino dla początkujących. Kolejny krok

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
EthernetServer server(80);
EthernetClient client;

const int numPins = 5;
int pins[] = {3, 4, 5, 6, 7};
int pinState[] = {0, 0, 0, 0, 0};
char line1[110];
char buffer[110];

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < numPins; i++)
  {
    pinMode(pins[i], OUTPUT);
  }
  Ethernet.begin(mac);

  server.begin();
}

void loop()
{
  client = server.available();
  if (client)
  {
    if (client.connected())
    {
      readHeader();
      // if (!pageNameIs("/"))
      // {
      //   client.stop();
      //   return;
      // }
      client.println(F("HTTP/1.1 200 OK"));
      client.println(F("Content-Type: text/html"));
      client.println();

      sendBody();
      client.stop();
    }
  }
}

void sendBody()
{
  client.println(F("<html><body>"));
  client.println(F("<h1>Piny wyj.</h1>"));
  client.println(F("<form method='GET'>"));
  setValuesFromParams();
  setPinStates();
  sendHTMLforPins();
  client.println(F("<input type='submit' value='Uaktualnij'/>"));
  client.println(F("</form>"));
  client.println(F("</body></html>"));
}

void sendHTMLforPins()
{
  for (int i = 0; i < numPins; i++)
  {
    client.print(F("<p>Pin "));
    client.print(pins[i]);
    client.print(F("<select name='"));
    client.print(i);
    client.println(F("'>"));
    client.print(F("<option value='0'"));
    if (pinState[i] == 0)
    {
      client.print(F(" selected"));
    }
    client.println(F(">Nieaktywny</option>"));
    client.print(F("<option value='1'"));
    if (pinState[i] == 1)
    {
      client.print(F(" selected"));
    }
    client.println(F(">Aktywny</option>"));
    client.println(F("</select></p>"));
  }
}

void setPinStates()
{
  for (int i = 0; i < numPins; i++)
  {
    digitalWrite(pins[i], pinState[i]);
  }
}

void setValuesFromParams()
{
  for (int i = 0; i < numPins; i++)
  {
    pinState[i] = valueOfParam(i + '0');
  }
}

void readHeader() // W efekcie zapełnia tablicę line1 nagłówkiem wiadomości (patrz 'line1 = ' niżej)
{
  readRequestLine(line1);
  while (readRequestLine(buffer) > 1 && buffer[0] != '\n')
  {
  }
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

// boolean pageNameIs(char *name)
// {
//   // nazwa strony rozpoczyna się od znaku na 4 pozycji kończy się spacją
//   int i = 4;
//   char ch = line1[i];
//   while (ch != ' ' && ch != '\n' && ch != '?')
//   {
//     if (name[i - 4] != line1[i])
//     {
//       return false;
//     }
//     i++;
//     ch = line1[i];
//   }
//   return true;
// }

int valueOfParam(char param) // param = 0 1 2 3 4
{
  for (int i = 0; i < strlen(line1); i++) // strlen(line1) = 16 / 36
  {
    if (line1[i] == param && line1[i + 1] == '=') // line1 = GET /?0=0&1=0&2=0&3=0&4
    {
      return (line1[i + 2] - '0');
    }
  }
  return 0;
}
