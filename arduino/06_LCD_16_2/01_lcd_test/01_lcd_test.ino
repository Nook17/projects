#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// int thisChar = 'a';      // to TEXT DIRECTION
// const int numRows = 2;   // to SET CURSOR
// const int numCols = 16;  // to SET CURSOR

void setup()
{
	lcd.begin(16, 2);     
  // lcd.print("Nook17");   // to DISPLAY
  // lcd.cursor();          // to TEXT DIRECTION
  // Serial.begin(9600);    // to SERIAL INPUT
  // lcd.begin(numCols, numRows);    // to SET CURSOR
}

void loop()
{
  /**************************************************************************
  *                              SCROLL 
  ***************************************************************************/
	// lcd.setCursor(16, 1);  // set the display to automatically scroll:
  // lcd.autoscroll();      // print from 0 to 9:
  // for (int thisChar = 0; thisChar < 10; thisChar++) {
  //   lcd.print(thisChar);
  //   delay(300);
  // }
  // lcd.noAutoscroll();    // turn off automatic scrolling
  // lcd.clear();           // clear screen for the next loop:

  /**************************************************************************
  *                              AUTOSCROLL 
  ***************************************************************************/
  lcd.setCursor(0, 0);      // set the cursor to (0,0):
  for (int thisChar = 0; thisChar < 10; thisChar++) {  // print from 0 to 9:
    lcd.print(thisChar);
    delay(500);
  }
  lcd.setCursor(16, 1);     // set the cursor to (16,1):
  lcd.autoscroll();         // set the display to automatically scroll:
  for (int thisChar = 0; thisChar < 10; thisChar++) {  // print from 0 to 9:
    lcd.print(thisChar);
    delay(500);
  }
  lcd.noAutoscroll();       // turn off automatic scrolling
  lcd.clear();              // clear screen for the next loop:

  /**************************************************************************
  *                            BLINK CURSOR
  ***************************************************************************/
  // lcd.noBlink();         // Turn off the blinking cursor:
  // delay(3000);
  // lcd.blink();           // Turn on the blinking cursor:
  // delay(3000);

  /**************************************************************************
  *                              DISPLAY
  ***************************************************************************/  
  // lcd.noDisplay();          // Turn off the display:
  // delay(500);
  // lcd.display();            // Turn on the display:
  // delay(500);

  /**************************************************************************
  *                           TEXT DIRECTION
  ***************************************************************************/   
  // if (thisChar == 'm') {       // reverse directions at 'm':
  //   lcd.rightToLeft();         // go right for the next letter
  // }
  // if (thisChar == 's') {       // reverse again at 's':
  //   lcd.leftToRight();        // go left for the next letter
  // }
  // if (thisChar > 'z') {       // reset at 'z':
  //   lcd.home();               // go to (0,0):
  //   thisChar = 'a';           // start again at 0
  // }
  // lcd.write(thisChar);        // print the character
  // delay(1000);                // wait a second:
  // thisChar++;                 // increment the letter:

  /**************************************************************************
  *                           SERIAL INPUT
  ***************************************************************************/ 
  // if (Serial.available()) {     // when characters arrive over the serial port...
  //   delay(100);                 // wait a bit for the entire message to arrive
  //   lcd.clear();                // clear the screen
  //   while (Serial.available() > 0) {  // read all the available characters
  //     lcd.write(Serial.read()); // display each character to the LCD
  //   }
  // }

  /**************************************************************************
  *                           SET CURSOR
  ***************************************************************************/ 
  // for (int thisLetter = 'a'; thisLetter <= 'z'; thisLetter++) {   // loop from ASCII 'a' to ASCII 'z':
  //   for (int  thisRow = 0; thisRow < numRows; thisRow++) {        // loop over the columns:
  //     for (int thisCol = 0; thisCol < numCols; thisCol++) {       // loop over the rows:
  //       lcd.setCursor(thisCol, thisRow);                          // set the cursor position:
  //       lcd.write(thisLetter);                                    // print the letter:
  //       delay(200);
  //     }
  //   }
  // }
}
