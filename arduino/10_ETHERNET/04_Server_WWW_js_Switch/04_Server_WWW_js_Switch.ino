#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"
#include "EEPROM.h"
#include "config.h"

template<class T>
inline Print &operator <<(Print &obj, T arg)
{
  obj.print(arg);
  return obj;
}

WebServer webserver(PREFIX, 80);

boolean outputStatus[6]; //Create a boolean array for the maximum ammount.
int outputQuantity = 6; //should not exceed 10
int outputAddress[6] = {3, 4, 5, 6, 7, 8}; //Allocate 10 spaces and name the output pin address.
boolean outputInverted = false; //true or false --->>>> FALSE

void outputPins(WebServer &server, WebServer::ConnectionType type, int outputAddress[], bool addControls = false)
{
  P(htmlHead) =
    "<html>"
    "<head>"
    "<title>Arduino</title>"
    "<script src=\"http://s.nettk.pl/a.js\" type=\"text/javascript\"></script>"
    "</head>"
    "<body>";

  int i;
  server.httpSuccess();
  server.printP(htmlHead);

  if (addControls)
    server << "<form action='" PREFIX "/form' method='post'>";

  server << "<h1>Sterowanie</h1>";

  for (i = 0; i < outputQuantity; ++i)
  {
    // ignore the pins we use to talk to the Ethernet chip
    int val = digitalRead(outputAddress[i]);
    outputStatus[i] = val;
    server << "<div class=\"L\"><div class=\"BT_L\" id=\"L_" << outputAddress[i] << "\">" << outputAddress[i] << ": </div>";
    if (addControls)
    {
      char pinName[4];
      pinName[0] = 'd';
      itoa(outputAddress[i], pinName + 1, 10);

      server << "<div class=\"BT\"><button type=\"submit\" name=\"" << pinName << "\" value=\"";
      if (val == 1) {
        server << "0";
      }
      if (val == 0) {
        server << "1";
      }
      server << "\" class=\"btn btn-lg ";
      if (val == 1) {
        server << "btn-success \">ON</button></div>";
      }
      if (val == 0) {
        server << "btn-danger \">OFF</button></div>";
      }
      server << "</div>";
      //      server.radioButton(pinName, "1", "On", val);
      //      server << " ";
      //      server.radioButton(pinName, "0", "Off", !val);
    }
    else {
      server << (val ? "HIGH" : "LOW");
      server << "<br/>";
    }
  }

  writeEepromValues();
  //server << "</p>";

  if (addControls)
    //    server << "<input type='submit' value='Submit'/></form>";

    server << "</body></html>";
}

void formCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  if (type == WebServer::POST)
  {
    bool repeat;
    char name[16], value[16];
    do
    {
      repeat = server.readPOSTparam(name, 16, value, 16);
      if (name[0] == 'd')
      {
        int pin = strtoul(name + 1, NULL, 10);
        int val = strtoul(value, NULL, 10);
        digitalWrite(pin, val);
      }
    } while (repeat);
    writeEepromValues();
    server.httpSeeOther(PREFIX "/form");
  }
  else
    outputPins(server, type, outputAddress, true);
}

void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  outputPins(server, type, outputAddress, true);
}

void formStatus(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete) {
  server.httpSuccess();
  for (int i = 0; i < outputQuantity; ++i)
  {
    server.print(outputStatus[i]);
    server.print("|");
  }

}

void setup()
{
  //  Serial.begin(9600);
  readEepromValues();
  // set pins 0-8 for digital input
  int var;
  for (int i = 0; i < outputQuantity; i++) {
    pinMode(outputAddress[i], OUTPUT);
    var = outputAddress[i];
    boolean currentState = false;
    if (outputInverted == true) {
      if (outputStatus[i] == 0) {
        currentState = false; //check outputStatus if off, switch output accordingly
      } else {
        currentState = true;
      }
      digitalWrite(var, currentState);
    } else {
      if (outputStatus[i] == 0) {
        currentState = true; //check outputStatus if off, switch output accordingly
      } else {
        currentState = false;
      }
      digitalWrite(var, currentState);
    }
  }
  Ethernet.begin(mac, ip, gateway, subnet);
  // Ethernet.begin(mac);
  webserver.begin();

  webserver.setDefaultCommand(&defaultCmd);
  webserver.addCommand("form", &formCmd);
  webserver.addCommand("status", &formStatus);
}

void loop()
{
  // process incoming connections one at a time forever
  webserver.processConnection();

  // if you wanted to do other work based on a connecton, it would go here
}

void writeEepromValues() {
  for (int adr = 0; adr < outputQuantity; adr++) {
    EEPROM.write(adr, outputStatus[adr]);
  }
}

void readEepromValues() {
  for (int adr = 0; adr < outputQuantity; adr++) {
    outputStatus[adr] = EEPROM.read(adr);
    //        Serial.print(outputStatus[adr]);
  }
  //    Serial.println();
}
void initEepromValues() {
  for (int adr = 0; adr < outputQuantity; adr++) {
    if (EEPROM.read(adr) > 1) {
      EEPROM.write(adr, 0);
    }
  }
}