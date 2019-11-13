# 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino"
# 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino"
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
# 19 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino"
# 20 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino" 2
# 21 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino" 2
# 22 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino" 2
# 23 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino" 2
# 24 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino" 2
# 25 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino" 2
# 39 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\11_RTC_DS1302\\02_RTC_SSD1306_Leonardo\\02_RTC_SSD1306_Leonardo.ino"
Adafruit_SSD1306 display(128, 64, 4, 5, 2, 1, 3); // Initialize the SSD1306
DS1302 rtc(A4, A3, A2); // Initialize the DS1302

const int ledPin = 13;
bool flag = 1;

void setup()
{
 pinMode(13, 0x1);
 pinMode(6, 0x1);
 pinMode(7, 0x1);
 pinMode(A1, 0x1);
 pinMode(A0, 0x1);
 digitalWrite(13, 0x0);
 digitalWrite(6, 0x0);
 digitalWrite(7, 0x1);
 digitalWrite(A1, 0x0);
 digitalWrite(A0, 0x1);

 display.begin(0x02 /*|< Gen. display voltage from 3.3V*/);
 rtc.halt(false);
 rtc.writeProtect(true); // Set the clock to run-mode, and disable the write protection
 rtc.setDOW(2); // Set Day-of-Week to FRIDAY
 rtc.setTime(9, 25, 0); // Set the time to 12:00:00 (24hr format)
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
 display.setTextSize(2); // Normal 1:1 pixel scale
 display.setTextColor(1 /*|< Draw 'on' pixels*/); // Draw white text

 display.setCursor(15, 5);
 display.println(rtc.getTimeStr());

 display.setTextSize(1); // Normal 1:1 pixel scale
 display.setCursor(55, 30); // Display abbreviated Day-of-Week in the lower left corner
 display.print(rtc.getDOWStr(1));

 display.setTextSize(2); // Normal 1:1 pixel scale
 display.setCursor(1, 50); // Display date in the lower right corner
 display.print(rtc.getDateStr());

 display.display(); // Show initial text
 delay(1000); // Wait one second before repeatingYou pressed the button 1 times.
}
