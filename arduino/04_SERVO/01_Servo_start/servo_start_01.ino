#include <Servo.h>

Servo nook_servo;

int pot = A0;
int val, degr;

void setup()
{
  nook_servo.attach(9);
  // Serial.begin(9600);
}

void loop()
{
  val = analogRead(pot);
  degr = map(val, 0, 1023, 0, 179);
  nook_servo.write(degr);
  delay(20);
}
