#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,140);

EthernetServer server(80);
String readString;
int stanz, stancz;


void setup() {
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  Ethernet.begin(mac, ip);
  server.begin();
  sensors.begin();
}


void loop() {

  sensors.requestTemperatures();  //temperature check request
  int jas= analogRead(A0);        // checking photoresistor (LDR) 
  jas=map(jas,0,700,100,0);       // convert readings from LDR to user friendly form
  stanz=analogRead(A5);           // check green LED
  stancz=analogRead(A4);          // check red LED
  
  EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (readString.length() < 100) {
          readString += c;     } 
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
        
                      //Print status depends of readings from A4 & A5
          client.println("<h3>STAN DIOD (na podstawie odczytu z pinow analogowych)</h3> ");
          client.print("Dioda czerwona ");
          if (stancz>100) {
            client.print("jest wlaczona"); 
          }
          else {
            client.print("jest wylaczona"); 
          }
          client.println("<br />");
          client.print("Dioda zielona ");
          if (stanz>100) {
            client.print("jest wlaczona"); 
          }
          else {
            client.print("jest wylaczona"); 
          }
          client.println("<br />");

                    // Print readings from sensors (DS18B20)
          client.println("<h2>A temperatura jest taka:</h2> ");
          client.print(sensors.getTempCByIndex(0)); 
          client.println(" stopni Celsjusza"); 
          client.print("<h2>I naslonecznienie wynosi:</h2> ");
          client.print(jas);
          client.print(" % ");
          client.println("<br />"); 
          
                      // Change state of LEDs
          client.println("<h2>Jeszcze wlacznik - wylacznik</h2>");

          client.println("<a href=\"/?on\"\">Zapal czerwona </a>"); 
          client.println("____"); 
          client.println("<a href=\"/?off\"\"> Zgas czerwona </a>"); 
          client.println("<br />");
          client.println("<a href=\"/?no\"\">Zapal zielona  </a>"); 
          client.println("_______"); 
          client.println("<a href=\"/?ffo\"\"> Zgas zielona</a>"); 
          client.println("<br /><br />");
          
          
                        // Insert picture
          client.println("<img src=\"http://www.elektromaras.pl/img/ElektroMarasLOGO.jpg\">");
                        
                        //Insert link
          client.println("<h3>Na koniec link zewnetrzny</h3>");
          client.println("<a href=\" https://www.youtube.com/channel/UCZqH_brXHGago171APziD0A\"\"> Kanal Elektromaras na You Tube </a>"); 
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
   
    delay(1);
    client.stop();
    
                //Change state of LESDs depends on user interaction 
    if(readString.indexOf("?on") >0) {
      digitalWrite(3, HIGH); 
    }
    if(readString.indexOf("?off") >0){
      digitalWrite(3, LOW); 
    }
    if(readString.indexOf("?no") >0) {
      digitalWrite(4, HIGH); 
    }
    if(readString.indexOf("?ffo") >0){
      digitalWrite(4, LOW); 
    }

    //clearing string for next read
    readString="";


  }
}

