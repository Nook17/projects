#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x00, 0x17, 0x00, 0x17, 0x00, 0x17 };
IPAddress ip(192, 168, 2, 117);

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);

  byte macBuffer[6];                  // create a buffer to hold the MAC address
  Ethernet.MACAddress(macBuffer);     // fill the buffer
  Serial.print("The MAC address is: ");
  for (byte octet = 0; octet < 6; octet++) {
    Serial.print(macBuffer[octet], HEX);
    if (octet < 5) {
      Serial.print('-');
    }
  }
  if (Ethernet.begin(mac))
  {
    Serial.println();
    Serial.print("The IP address is: ");
    Serial.println(Ethernet.localIP());
  }
  else
  {
    Serial.println("Nie polaczono z siecia");
  }
}

void loop () {}
