//Lab 4 Starter
// C++ code
//Note: Upon downloading, this code does nothing except run without errors at a period of 500ms
//      It is up to you to figure out how to manipulate these timing details for your own purposes
#include "Timer.h"

enum STATE {INIT, PRESPEED1, SPEED1, PRESPEED2, SPEED2, OFF } gState = INIT;
int ledPin = 2;
int buttonPin = 12;
int buttonState = 0;
int count = 0;


void tick(void) {
  
  // transitions
  switch (gState) {
    case INIT:
    if (buttonState == 0){
      gState = INIT;
    }
    else if (buttonState == 1){
      gState = PRESPEED1;
    }
    break;

    case PRESPEED1:
    gState = SPEED1;
    break;

    case SPEED1:
    if (buttonState == 0){
      gState = SPEED1;
    }
    else if (buttonState == 1){
      gState = PRESPEED2;
    }
    break;

    case PRESPEED2:
    gState = SPEED2;
    break;

    case SPEED2:
    if (buttonState == 0){
      gState = SPEED2;
    }
    else if (buttonState == 1){
      gState = OFF;
    }
    break;

    case OFF:
    if (buttonState == 0){
      gState = OFF;
    }
    else if (buttonState == 1){
      gState = PRESPEED1;
    }
    break;

    default:
    gState = INIT;
    break;
  
  }
  
  // actions
  switch (gState) {
    case INIT:
    count = 0;
    digitalWrite(ledPin, LOW);
    break;

    case PRESPEED1:
    if(count > 3){
      digitalWrite(ledPin,  !digitalRead(ledPin));
      count = 0;
    }
    else {
      count = count +1;
    }
    break;

    case SPEED1:
    if(count > 3){
      digitalWrite(ledPin,  !digitalRead(ledPin));
      count = 0;
    }
    else {
      count = count +1;
    }
    break;

    case PRESPEED2:
    if(count > 1){
      digitalWrite(ledPin,  !digitalRead(ledPin));
      count = 0;
    }
    else {
      count = count +1;
    }
    break;

    case SPEED2:
    if(count > 1){
      digitalWrite(ledPin,  !digitalRead(ledPin));
      count = 0;
    }
    else {
      count = count +1;
    }
    break;

    case OFF:
    digitalWrite(ledPin, LOW);
    break;



  }
}

void setup() {
  TimerSet(100); //this value (500) is the period in ms
  TimerOn();
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  buttonState = digitalRead(12);
  tick();
  while(!TimerFlag){}
  TimerFlag = 0;  
}