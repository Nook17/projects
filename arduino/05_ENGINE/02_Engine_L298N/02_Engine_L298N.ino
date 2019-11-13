#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // for MAC
// LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  // for Windows
const int pot = A0, sw = 11, in1 = 9, in2 = 8, ena = 10;
int ena_pwm, val, stan = 0, progress, progress_max = 0;

void setup()
{
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

int state()
{
  if (digitalRead(sw))
  {
    delay(20);
    stan = !stan;
    while (digitalRead(sw))
      ;
    delay(20);
  }
  return stan;
}

void direction()
{
  switch (stan)
  {
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

void speed()
{
  val = analogRead(pot);
  ena_pwm = map(val, 0, 1023, 0, 254);
  progress = map(val, 0, 1023, 0, 16);
  analogWrite(ena, ena_pwm);
}

void screan()
{
  lcd.setCursor(0, 0);
  lcd.print("kierunek");
  lcd.setCursor(9, 0);
  if (!stan)
  {
    lcd.print("--->");
  }
  else
  {
    lcd.print("<---");
  }

  if (progress_max <= progress)
  {
    lcd.setCursor(0, 1);
    for (int i = 0; i <= progress; i++)
    {
      lcd.print("*");
    }
    progress_max = progress;
  }
  else
  {
    lcd.clear();
    progress_max = progress;
  }
}