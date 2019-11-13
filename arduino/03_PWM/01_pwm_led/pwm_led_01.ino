int led = 9;
int pot = A0;
int val, map_pwm;

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
