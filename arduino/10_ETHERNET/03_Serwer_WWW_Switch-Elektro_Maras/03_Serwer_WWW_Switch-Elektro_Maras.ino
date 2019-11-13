#include <SPI.h>
#include <Ethernet.h>
// #include <OneWire.h>
// #include <DallasTemperature.h>

// #define ONE_WIRE_BUS 2
// OneWire oneWire(ONE_WIRE_BUS);
// DallasTemperature sensors(&oneWire);

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// IPAddress ip(192,168,1,140);

EthernetServer server(80);
String readString;
int stanz = 0, stancz = 0;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  Ethernet.begin(mac);
  server.begin();
  // sensors.begin();
}

void loop() {

  // sensors.requestTemperatures();   // temperature check request
  // int jas= analogRead(A0);         // checking photoresistor (LDR) 
  // jas=map(jas,0,700,100,0);        // convert readings from LDR to user friendly form
  // stanz=analogRead(A5);               // check green LED
  // stancz=analogRead(A4);              // check red LED
  
  EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (readString.length() < 100) {
          readString += c;
        } 
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");         // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          /*** Print status depends of readings from A4 & A5 ***/
          client.println("<h3>STAN DIOD (na podstawie odczytu z pinow analogowych)</h3>");
          client.print("Dioda czerwona ");
          if (stancz)
            client.print("jest wlaczona"); 
          else
            client.print("jest wylaczona"); 
          client.println("<br />");
          client.print("Dioda zielona ");
          if (stanz)
            client.print("jest wlaczona"); 
          else
            client.print("jest wylaczona"); 
          client.println("<br />");
          /*** Print readings from sensors (DS18B20) **/
          // client.println("<h2>A temperatura jest taka:</h2> ");
          // client.print(sensors.getTempCByIndex(0)); 
          // client.println(" stopni Celsjusza"); 
          // client.print("<h2>I naslonecznienie wynosi:</h2> ");
          // client.print(jas);
          // client.print(" % ");
          // client.println("<br />"); 
          /*** Change state of LEDs ***/
          client.println("<h2>Jeszcze wlacznik - wylacznik</h2>");
          client.println("<a href=\"/?on\"\">Zapal czerwona</a>"); 
          client.println("____"); 
          client.println("<a href=\"/?off\"\">Zgas czerwona</a>"); 
          client.println("<br />");
          client.println("<a href=\"/?no\"\">Zapal zielona</a>"); 
          client.println("______"); 
          client.println("<a href=\"/?ffo\"\">Zgas zielona</a>"); 
          client.println("<br /><br />");
          /*** Insert picture ***/
          // client.println("<img src=\"http://nook17.pl/user/assets/img/nook/Nook17_1_1_80_kwadrat.png\">");
          /*** Insert link ***/
          // client.println("<h3>Na koniec link zewnetrzny</h3>");
          // client.println("<a href=\"https://www.youtube.com/channel/UCP42VBk1h5RgM4x6LJcRKBA\"\">Nook17.pl</a>"); 
          // client.println("</html>");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;          // you're starting a new line
        } 
        else if (c != '\r') {
          currentLineIsBlank = false;          // you've gotten a character on the current line
        }
      }
    }
   
    delay(1);
    client.stop();
    
    /*** Change state of LESDs depends on user interaction ***/
    if(readString.indexOf("?on") > 0) {
      digitalWrite(3, HIGH);
      stancz = 1;
    }
    if(readString.indexOf("?off") > 0) {
      digitalWrite(3, LOW);
      stancz = 0;
    }
    if(readString.indexOf("?no") > 0) {
      digitalWrite(4, HIGH);
      stanz = 1;
    }
    if(readString.indexOf("?ffo") > 0) {
      digitalWrite(4, LOW);
      stanz = 0;
    }

    readString="";    //clearing string for next read
  }
}
