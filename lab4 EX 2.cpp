//Lab 4 Starter
// C++ code
//Note: Upon downloading, this code does nothing except run without errors at a period of 500ms
//      It is up to you to figure out how to manipulate these timing details for your own purposes
#include "Timer.h"

enum STATE {RED, GREEN, YELLOW} gState = RED;
int buttonState = 0;
int redPin = 5;
int greenPin = 4;
int yellowPin = 3;
int buttonPin = 13;

void tick(void) {
  
  // transitions
  switch (gState) {
    case RED:
    if(buttonState == 0){
      gState = RED;
    }
    else if (buttonState == 1){
      gState = GREEN;
      TimerSet(10000);
    }
    break;
    


    case GREEN:
    TimerSet(5000);
    gState = YELLOW;
    break;

    case YELLOW:
    TimerSet(1000);
    gState = RED;
    break;


    default:
    gState = RED;
    break;
  }
  
  // actions
  switch (gState) {
    case RED:
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
    break;

    case GREEN:
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPin, LOW);
    break;
    
    case YELLOW:
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(redPin, LOW);
    break;

  }
}

void setup() {
  TimerSet(500); //this value (500) is the period in ms
  TimerOn();
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  tick();
  while(!TimerFlag){}
  TimerFlag = 0;  
  
}