#include <Arduino.h>
#line 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\03_PWM\\01_pwm_led\\pwm_led_01.ino"
#line 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\03_PWM\\01_pwm_led\\pwm_led_01.ino"
int led = 9;
int pot = A0;
int val, map_pwm;

#line 5 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\03_PWM\\01_pwm_led\\pwm_led_01.ino"
void setup();
#line 12 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\03_PWM\\01_pwm_led\\pwm_led_01.ino"
void loop();
#line 5 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\03_PWM\\01_pwm_led\\pwm_led_01.ino"
void setup()
{
 Serial.begin(9600); 
 pinMode(pot, INPUT);
 pinMode(led, OUTPUT);
}

void loop()
{
  val = analogRead(pot);
  map_pwm = map(val, 0, 1023, 0, 254);
  analogWrite(led, map_pwm);
  Serial.print("Potencjometr: ");
  Serial.print(val);
  Serial.print(" --------- Mapowanie: ");
  Serial.println(map_pwm);

//  for (int i = 0; i <= 250; i++)
//  {
//   analogWrite(pwm, i);
//   tone(pwm, i);
//   delay(5);
//  }
//  for (int i = 250; i >= 1; i--)
//  {
//   analogWrite(pwm, i);
//   delay(1);
//  }
}

