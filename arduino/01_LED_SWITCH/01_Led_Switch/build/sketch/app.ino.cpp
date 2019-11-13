#include <Arduino.h>
#line 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\01_LED_SWITCH\\01_Led_Switch\\app.ino"
#line 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\01_LED_SWITCH\\01_Led_Switch\\app.ino"
int sw = 11;
int led_g = 10;
int led_o = 9;
int led_r = 8;
int stan = 0;

#line 7 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\01_LED_SWITCH\\01_Led_Switch\\app.ino"
void setup();
#line 15 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\01_LED_SWITCH\\01_Led_Switch\\app.ino"
void check();
#line 41 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\01_LED_SWITCH\\01_Led_Switch\\app.ino"
void loop();
#line 7 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\01_LED_SWITCH\\01_Led_Switch\\app.ino"
void setup()
{
  pinMode(led_g, OUTPUT);
  pinMode(led_o, OUTPUT);
  pinMode(led_r, OUTPUT);
  pinMode(sw, INPUT);
}

void check() {
    switch(stan) {
        case 1:
            digitalWrite(led_g, HIGH);
            digitalWrite(led_o, LOW);
            digitalWrite(led_r, LOW);
        break;
        case 2:
            digitalWrite(led_g, HIGH);
            digitalWrite(led_o, HIGH);
            digitalWrite(led_r, LOW);
        break;
        case 3:
            digitalWrite(led_g, LOW);
            digitalWrite(led_o, LOW);
            digitalWrite(led_r, HIGH);
        break;
        case 4:
            digitalWrite(led_g, LOW);
            digitalWrite(led_o, HIGH);
            digitalWrite(led_r, LOW);
            stan = 0;
        break;
    }
}

void loop()
{
  if(digitalRead(sw))
  {
    delay(20);
    stan++;
    check();
    while(digitalRead(sw));
    delay(20);
  }
}
