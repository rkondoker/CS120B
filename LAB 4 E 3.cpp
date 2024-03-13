//Lab 4 Starter
// C++ code
//Note: Upon downloading, this code does nothing except run without errors at a period of 500ms
//      It is up to you to figure out how to manipulate these timing details for your own purposes
 #include "Timer.h"

enum STATE {INIT, ON} gState = INIT;
int ledPin = 13;
int photoInput = A0;
int photonum = 0;
int count = 0;



void tick(void) {
  
  // transitions
  switch (gState) {
    case INIT:
    if(photonum < 10){
      count ++;
    }
    else if (photonum > 10){
      count = 0;
    }
    if(count > 25){
      gState = ON;
      count = 0;
    }
    else if (count < 25){
      gState = INIT;
    }
    break;

    case ON:
    if (photonum > 10){
      gState = INIT;
    }
    else if (photonum < 10){
      gState = ON;
    }
    break;

    default:
    gState = INIT;
    break;
  }
  
  // actions
  switch (gState) {
    case INIT:
    digitalWrite(2, LOW);
    break;

    case ON:
    digitalWrite(2, HIGH);
    break;
    
  }
}

void setup() {
  TimerSet(200); //this value (500) is the period in ms
  TimerOn();
  Serial.begin(9600);

}

void loop()
{
  photonum = analogRead(photoInput);
  tick();
  while(!TimerFlag){}
  TimerFlag = 0;  
  Serial.print(photonum);
  Serial.print('\n');
  //Serial.print(count);
  Serial.print('\n');
}