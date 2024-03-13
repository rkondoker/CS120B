#include "Timer.h"

unsigned int score = 0;
int buttonState = 0;
int count = 0;
int displayCount = 0;
bool moveRightDone = 0;
int currLed = 0;
int lightTime = 10;

// Helper Function display a number on ONE digit

// gSegPins
// An array of pins of the arduino that are connected
// to segments a, b, c, d, e... g in that order.
char gSegPins[] = {A10, A7, A13, A14, A15, A9, A12};


// displayNumTo7Seg
// displays one number (between 0 and 9) "targetNum" on the digit conneceted to "digitPin"
// E.g. If I wanted to display the number 6 on the third digit of my display.
// and the third digit was connected to pin A0, then I'd write: displayNumTo7Seg(6, A0);
void displayNumTo7Seg(unsigned int targetNum, int digitPin) {


    // A map of integers to the respective values needed to display
    // a value on one 7 seg digit.
    unsigned char encodeInt[10] = {
        // 0     1     2     3     4     5     6     7     8     9
        0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67,
    };
    // Make sure the target digit is off while updating the segments iteratively
    digitalWrite(digitPin, HIGH);
    // Update the segments
    for (int k = 0; k < 7; ++k) {
        digitalWrite(gSegPins[k], encodeInt[targetNum] & (1 << k));
    }
    // Turn on the digit again
    digitalWrite(digitPin, LOW);

}

void ledOff(){
  for(int i = 2; i < 11; i++){
    digitalWrite(i, LOW);
  }
}

enum DISPLAY_STATES{ DIG1, DIG2} dState = DIG1;

void tickDisplay(){
  switch (dState){

    case DIG1:
    dState = DIG2;
    break;

    case DIG2:
    dState = DIG1;
    break;

    default:
    dState = DIG1;
    break;
  }

  switch(dState){

    case DIG1:
    displayCount = 0;
    while(displayCount < 10){
      digitalWrite(A11, LOW);
      displayNumTo7Seg(score % 10, A8);
      digitalWrite(A8, HIGH);
      displayCount++;
    }
    break;

    case DIG2:
    displayCount = 0;
    while(displayCount < 10 ){
      digitalWrite(A8, LOW);
      displayNumTo7Seg(score / 10, A11);
      digitalWrite(A11, HIGH);
      displayCount++;
    }
    break;

  }


}


enum LED_STATES{LED1, LED2, LED3, LED4, LED5, LED6, LED7, FREEZE} ledState = LED1;
void tickLed(){
  switch (ledState){

    case FREEZE:
    if(buttonState == 0){
      ledOff();
      digitalWrite(currLed, HIGH);
      ledState = FREEZE;
    }
    else {
      switch(currLed){

        case 3:
        ledState = LED2;
        break;

        case 4:
        ledState = LED3;
        break;

        case 5:
        ledState = LED4;
        break;

        case 6:
        ledState = LED5;
        break;

        case 7:
        ledState = LED6;
        break;

        case 8:
        ledState = LED7;
        break;

        case 10:
        ledState = LED1;
        break;
      }
    }
    break;


    case LED1:
    if(buttonState == 0){
      currLed = 10;
      score = 0;
      ledState = FREEZE;
      
    }
    else {
    if (count < lightTime){
      ledOff();
      digitalWrite(10, HIGH);
      count ++;
    }
    else {
      count = 0;
      moveRightDone = 0;
      ledState = LED2;
    }
    }
    break;

    case LED2:
    if(buttonState == 0){
      currLed = 3;
      score = 0;
      ledState = FREEZE;
    }
    else {
    if(count < lightTime){
      ledOff();
      digitalWrite(3, HIGH);
      count++;
    }
    else{
      count = 0;
      if(moveRightDone){
        ledState = LED1;
      }
      else {
        ledState = LED3;
      }
    }
    }
      break;

    case LED3:
    if(buttonState == 0){
      currLed = 4;
      score = 0;
      ledState = FREEZE;
    }
    else {
    if(count < lightTime){
      ledOff();
      digitalWrite(4, HIGH);
      count++;
    }
    else {
      count = 0;
      if(moveRightDone){
        ledState = LED2;
      }
      else {
        ledState = LED4;
      }
    }
    }
      break;

    case LED4:
    if(buttonState == 0){
      currLed = 5;
      score++;
      ledState = FREEZE;
    }
    else {
    if(count < lightTime){
      ledOff();
      digitalWrite(5, HIGH);
      
      count++;
    }
    else {
      count = 0;
      if(moveRightDone){
        ledState = LED3;
      }
      else {
        ledState = LED5;
      }
    }
    }
      break;

    case LED5:
    if(buttonState == 0){
      currLed = 6;
      score = 0;
      ledState = FREEZE;
    }
    else {
    if(count < lightTime){
      ledOff();
      digitalWrite(6, HIGH);
      count ++;
    }
    else {
      count = 0;
      if(moveRightDone){
        ledState = LED4;
      }
      else {
        ledState = LED6;
      }
    }
    }
      break;

    case LED6:
    
    if(buttonState == 0){
      currLed = 7;
      score = 0;
      ledState = FREEZE;
    }
    else {
    if(count < lightTime){
      ledOff();
      digitalWrite(7, HIGH);
      count++;
    }
    else {
      count =0;
      if(moveRightDone){
        ledState = LED5;
      }
      else {
        ledState = LED7;
      }
    }
    }
      break;

    case LED7:
    if(buttonState == 0){
      currLed = 8;
      score = 0;
      ledState = FREEZE;
    }
    else {
    if(count < lightTime){
      ledOff();
      digitalWrite(8, HIGH);
      count++;
    }
    else {
      count = 0;
      moveRightDone = 1;
      ledState = LED6;
    }
    }
      break;
    
    default:
    ledState = LED1;
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(13, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(A7, OUTPUT);
  pinMode(A8, OUTPUT);
  pinMode(A9, OUTPUT);
  pinMode(A10, OUTPUT);
  pinMode(A11, OUTPUT);
  pinMode(A12, OUTPUT);
  pinMode(A13, OUTPUT);
  pinMode(A14, OUTPUT);
  pinMode(A15, OUTPUT);

  Serial.begin(9600);
  TimerSet(10); //this value is the period in ms
  TimerOn();
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(13);
  tickLed();
  tickDisplay();
  Serial.print(score);
  Serial.print("\n");
  while(!TimerFlag){}
  TimerFlag = 0; 
}
