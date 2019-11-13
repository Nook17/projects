int pin = A0;
int odczyt, los;
float volt;
bool flag = 0;

void setup()
{
	Serial.begin(9600);
  pinMode(pin, INPUT);
}

void loop()
{
	odczyt = analogRead(pin);
  // randomSeed(odczyt);
  volt = (odczyt * 5.00) / 1023.00;
  // if(!flag) {
  //   for(int i = 0; i<=10; i++) {
  //     los = random(100);
  //     Serial.println(los);
  //     if(i == 10)
  //       flag = 1;  
  //   }  
  // }
  Serial.println(volt);
  delay(20);
}
