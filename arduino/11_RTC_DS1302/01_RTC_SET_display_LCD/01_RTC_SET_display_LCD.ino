// DS1302_LCD 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// I assume you know how to connect the DS1302 and LCD.
// DS1302:  RST / CE  -> Arduino Digital A2
//          DAT / I/O -> Arduino Digital A1
//          CLK       -> Arduino Digital A0
// LCD:     DB7       -> Arduino Digital 2
//          DB6       -> Arduino Digital 3
//          DB5       -> Arduino Digital 4
//          DB4       -> Arduino Digital 5
//          E         -> Arduino Digital 6
//          RS        -> Arduino Digital 7

#include <LiquidCrystal.h>
#include <DS1302.h>

DS1302 rtc(A2, A1, A0);               // Init the DS1302
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  // Init the LCD

void setup()
{
  lcd.begin(16, 2);           // Setup LCD to 16x2 characters
  rtc.halt(false);
  rtc.writeProtect(true);     // Set the clock to run-mode, and disable the write protection
  rtc.setDOW(MONDAY);         // Set Day-of-Week to FRIDAY
  rtc.setTime(14, 28, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(9, 9, 2019);    // Set the date to August 6th, 2010
}

void loop()
{
  lcd.setCursor(4, 0);        // Display time centered on the upper line
  lcd.print(rtc.getTimeStr());
  
  lcd.setCursor(0, 1);        // Display abbreviated Day-of-Week in the lower left corner
  lcd.print(rtc.getDOWStr(FORMAT_SHORT));
  
  lcd.setCursor(6, 1);        // Display date in the lower right corner
  lcd.print(rtc.getDateStr());

  delay (1000);               // Wait one second before repeating :)
}