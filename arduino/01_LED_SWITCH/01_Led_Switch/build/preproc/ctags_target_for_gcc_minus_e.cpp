# 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\01_LED_SWITCH\\01_Led_Switch\\app.ino"
# 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\01_LED_SWITCH\\01_Led_Switch\\app.ino"
int sw = 11;
int led_g = 10;
int led_o = 9;
int led_r = 8;
int stan = 0;

void setup()
{
  pinMode(led_g, 0x1);
  pinMode(led_o, 0x1);
  pinMode(led_r, 0x1);
  pinMode(sw, 0x0);
}

void check() {
    switch(stan) {
        case 1:
            digitalWrite(led_g, 0x1);
            digitalWrite(led_o, 0x0);
            digitalWrite(led_r, 0x0);
        break;
        case 2:
            digitalWrite(led_g, 0x1);
            digitalWrite(led_o, 0x1);
            digitalWrite(led_r, 0x0);
        break;
        case 3:
            digitalWrite(led_g, 0x0);
            digitalWrite(led_o, 0x0);
            digitalWrite(led_r, 0x1);
        break;
        case 4:
            digitalWrite(led_g, 0x0);
            digitalWrite(led_o, 0x1);
            digitalWrite(led_r, 0x0);
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
