#include <Arduino.h>
#line 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\05_ENGINE\\02_Engine_L298N\\02_Engine_L298N.ino"
#line 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\05_ENGINE\\02_Engine_L298N\\02_Engine_L298N.ino"
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const int pot = A0, sw = 11, in1 = 9, in2 = 8, ena = 10;
int ena_pwm, val, stan = 0, progress, progress_max = 0;
// char ascii = 120;

#line 8 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\05_ENGINE\\02_Engine_L298N\\02_Engine_L298N.ino"
void setup();
#line 19 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\05_ENGINE\\02_Engine_L298N\\02_Engine_L298N.ino"
void loop();
#line 27 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\05_ENGINE\\02_Engine_L298N\\02_Engine_L298N.ino"
int state();
#line 37 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\05_ENGINE\\02_Engine_L298N\\02_Engine_L298N.ino"
void direction();
#line 50 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\05_ENGINE\\02_Engine_L298N\\02_Engine_L298N.ino"
void speed();
#line 57 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\05_ENGINE\\02_Engine_L298N\\02_Engine_L298N.ino"
void screan();
#line 8 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\05_ENGINE\\02_Engine_L298N\\02_Engine_L298N.ino"
void setup()
{
  // Serial.begin(9600);
  lcd.begin(16, 2);  
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(ena, OUTPUT);
  pinMode(pot, INPUT);
  pinMode(sw, INPUT);
}

void loop()
{
  screan();
  state();
  direction();
  speed();
}

int state() {
	if(digitalRead(sw)) {
    delay(20);
    stan = !stan;
    while(digitalRead(sw));
    delay(20);
  }
  return stan;
}

void direction() {
  switch(stan) {
    case 0:
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      break;
    case 1:
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      break;
  }
}

void speed() {
  val = analogRead(pot);
  ena_pwm = map(val, 0, 1023, 0, 254);
  progress = map(val, 0, 1023, 0, 16);
  analogWrite(ena, ena_pwm);
}

void screan() {
  lcd.setCursor(0, 0);
  // lcd.home();
  lcd.print("kierunek");
  lcd.setCursor(9, 0);
  if(!stan) {
    lcd.print("--->");
  } else {
    lcd.print("<---");
  }

  if(progress_max <= progress) {
    lcd.setCursor(0, 1);
    for(int i = 0; i <= progress; i++) {
      lcd.print("*");
    }
    progress_max = progress;
  }
  else {
    lcd.clear();
    progress_max = progress;

  }
  
}
