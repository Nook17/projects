# 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\08_I2C_WIRE\\01_Rx_Tx_UNO_Leonardo\\UNO_Wire_Slave_Receiver\\UNO_Wire_Slave_Receiver.ino"
# 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\08_I2C_WIRE\\01_Rx_Tx_UNO_Leonardo\\UNO_Wire_Slave_Receiver\\UNO_Wire_Slave_Receiver.ino"
// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>
// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this
// Created 29 March 2006
// This example code is in the public domain.

# 10 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\08_I2C_WIRE\\01_Rx_Tx_UNO_Leonardo\\UNO_Wire_Slave_Receiver\\UNO_Wire_Slave_Receiver.ino" 2
# 11 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\08_I2C_WIRE\\01_Rx_Tx_UNO_Leonardo\\UNO_Wire_Slave_Receiver\\UNO_Wire_Slave_Receiver.ino" 2
# 12 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\08_I2C_WIRE\\01_Rx_Tx_UNO_Leonardo\\UNO_Wire_Slave_Receiver\\UNO_Wire_Slave_Receiver.ino" 2
# 13 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\08_I2C_WIRE\\01_Rx_Tx_UNO_Leonardo\\UNO_Wire_Slave_Receiver\\UNO_Wire_Slave_Receiver.ino" 2

/* Declaration for SSD1306 display connected using software SPI (default case):

*                       white  color

* MOSI / DIN / SDA / D1 - 10    11                         

* CLK / SCK / SCL  / D0 - 9     12

* DC / A0               - 12    9

* CS                    - 13    10

* RESET                 - 11    8

*/
# 27 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\08_I2C_WIRE\\01_Rx_Tx_UNO_Leonardo\\UNO_Wire_Slave_Receiver\\UNO_Wire_Slave_Receiver.ino"
Adafruit_SSD1306 display(128, 64, 11, 12, 9, 8, 10);

void setup() {
  display.begin(0x02 /*|< Gen. display voltage from 3.3V*/);
  Wire.begin(8); // join i2c bus with address #8

  display.setTextColor(1 /*|< Draw 'on' pixels*/); // Draw white text

  Wire.onReceive(receiveEvent); // register event
  // Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  display.clearDisplay();
  display.setTextSize(1); // Normal 1:1 pixel scale
  display.setCursor(55, 10); // Start at top-left corner
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    display.print(c);
    // Serial.print(c);           // print the character
  }
  int x = Wire.read(); // receive byte as an integer
  // Serial.println(x);             // print the integer
  display.setTextSize(2); // Normal 1:1 pixel scale
  display.setCursor(50, 30); // Start at top-left corner
  display.println(x); // print the integer
  display.display(); // Show initial text
}
