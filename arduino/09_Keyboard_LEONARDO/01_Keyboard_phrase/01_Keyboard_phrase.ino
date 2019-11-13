#include "Keyboard.h"
#include "Mouse.h"

const int buttonPin = 4;          // input pin for pushbutton
int previousButtonState = HIGH;   // for checking the state of a pushButton
int counter = 0;                  // button push counter

void setup() {
  // make the pushButton pin an input:
  pinMode(buttonPin, INPUT);
  // initialize control over the keyboard:
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  // if the button state has changed,
  if ((buttonState != previousButtonState)
      // and it's currently pressed:
      && (buttonState == HIGH)) {
    // increment the button counter
    counter++;
    // type out a message
    Keyboard.print("You pressed the button ");
    Keyboard.print(counter);
    Keyboard.println(" times.");
    Mouse.move(random(-100, 100), random(-100, 100));
  }
  // save the current button state for comparison next time:
  previousButtonState = buttonState;
}


// char phrase[] = "haslo";
// void setup()
// {
//   Keyboard.begin();
//   delay(5000);
//   Keyboard.println(phrase);
// }
// void loop()
// {
// }