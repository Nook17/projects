# 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\05_ENGINE\\01_Engine_MOSFET\\Engine_MOSFET_01.ino"
# 1 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\05_ENGINE\\01_Engine_MOSFET\\Engine_MOSFET_01.ino"
# 2 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\05_ENGINE\\01_Engine_MOSFET\\Engine_MOSFET_01.ino" 2

/************************************************

*  WERSJA NA POTENCJOMETR

************************************************/
# 7 "c:\\Users\\nook1_000\\OneDrive\\Elektronika\\ARDUINO\\Projekty\\05_ENGINE\\01_Engine_MOSFET\\Engine_MOSFET_01.ino"
// LiquidCrystal lcd(2, 3, 4, 5, 6, 7);  // for MAC
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // for Windows
int pot = A0;
int mosfet_control = 11;
int pwm, val;
float v_engine;

void setup()
{
  lcd.begin(16, 2);
  pinMode(pot, 0x0);
  pinMode(mosfet_control, 0x1);
}

void loop()
{
  val = analogRead(pot);
  pwm = map(val, 0, 1023, 0, 254);
  v_engine = val * 6.00 / 1023.00;
  analogWrite(mosfet_control, pwm);
  display();
  delay(50);
}

void display()
{
  lcd.setCursor(0, 0);
  lcd.print("Napiecie :");
  lcd.setCursor(0, 1);
  // if (v_engine < 10)
  // {
  // lcd.clear();
  lcd.print(v_engine);
  lcd.setCursor(5, 1);
  lcd.print("V");
  // }
  // else
  // {
  //   // lcd.clear();
  //   lcd.print(v_engine);
  //   lcd.setCursor(6, 1);
  //   lcd.print("V");
  // }
}

/************************************************

*   WERSJA NA PRZYCISK

*************************************************



int sw = 2;

int mosfet_control = 11;

bool stan = 0;



void setup()

{

	pinMode(sw, INPUT);

	pinMode(mosfet_control, OUTPUT);

}



void loop()

{

	if(digitalRead(sw)) {

    delay(20);

    stan = !stan;

    digitalWrite(mosfet_control, stan);

    while(digitalRead(sw));

    delay(20);

  }

}

*/
