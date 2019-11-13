#include <Arduino.h>
#line 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino"
#line 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino"
/* 02_RTC_SSD1306_Leonardo
*      ---> Nook17 <---
*********** DS1302 **********
* RST / CE              -> A4
* DAT / I/O             -> A3
* CLK                   -> A2
* GND                   -> A1
* VCC                   -> A0
********** SSD1306 **********
* VCC                         -> 7
* GND                         -> 6
* CLK / SCK / SCL  / D0       -> 5
* MOSI / DIN / SDA / D1 / SDI -> 4
* CS / SS                     -> 3
* DC / A0 / MISO / SDO        -> 2
* RST                         -> 1
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DS1302.h>
#include "Logo.h"

#define DS1302_RST A4
#define DS1302_DAT A3
#define DS1302_CLK A2
#define DS1302_GND A1
#define DS1302_VCC A0
#define OLED_VCC 7
#define OLED_GND 6
#define OLED_CLK 5
#define OLED_MOSI 4
#define OLED_CS 3
#define OLED_DC 2
#define OLED_RST 1

Adafruit_SSD1306 display(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS); // Initialize the SSD1306
DS1302 rtc(DS1302_RST, DS1302_DAT, DS1302_CLK);                                     // Initialize the DS1302

const int ledPin = LED_BUILTIN;
bool flag = 1;

#line 45 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino"
void setup();
#line 66 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino"
void loop();
#line 45 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino"
void setup()
{
 pinMode(LED_BUILTIN, OUTPUT);
 pinMode(OLED_GND, OUTPUT);
 pinMode(OLED_VCC, OUTPUT);
 pinMode(DS1302_GND, OUTPUT);
 pinMode(DS1302_VCC, OUTPUT);
 digitalWrite(LED_BUILTIN, LOW);
 digitalWrite(OLED_GND, LOW);
 digitalWrite(OLED_VCC, HIGH);
 digitalWrite(DS1302_GND, LOW);
 digitalWrite(DS1302_VCC, HIGH);

 display.begin(SSD1306_SWITCHCAPVCC);
 rtc.halt(false);
 rtc.writeProtect(true);   // Set the clock to run-mode, and disable the write protection
 rtc.setDOW(TUESDAY);      // Set Day-of-Week to FRIDAY
 rtc.setTime(9, 25, 0);    // Set the time to 12:00:00 (24hr format)
 rtc.setDate(3, 10, 2019); // Set the date to August 6th, 2010
}

void loop()
{
 if (flag)
 {
  display.clearDisplay();
  display.drawBitmap(40, 10, nook17_bmp, 50, 49, 1); // drawBitmap(x, y, name, width, height, color)
  display.display();
  flag = 0;
  delay(1000);
 }
 display.clearDisplay();
 display.setTextSize(2);      // Normal 1:1 pixel scale
 display.setTextColor(WHITE); // Draw white text

 display.setCursor(15, 5);
 display.println(rtc.getTimeStr());

 display.setTextSize(1);    // Normal 1:1 pixel scale
 display.setCursor(55, 30); // Display abbreviated Day-of-Week in the lower left corner
 display.print(rtc.getDOWStr(FORMAT_SHORT));

 display.setTextSize(2);   // Normal 1:1 pixel scale
 display.setCursor(1, 50); // Display date in the lower right corner
 display.print(rtc.getDateStr());

 display.display(); // Show initial text
 delay(1000);       // Wait one second before repeatingYou pressed the button 1 times.
}

