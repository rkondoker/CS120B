#include "Timer.h"
#include <LiquidCrystal.h>
#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;
const int X_pin = 1; // analog pin connected to X output
LiquidCrystal lcd(52, 50, 53, 48, 51, 46); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
const int trigPin = 13;
const int echoPin = 12;
long duration;
int cmDist, inchDist;
int xVal;
Stepper stepMotor(stepsPerRevolution, 2, 4, 3, 5);

enum STATE{INIT, LEFT, RIGHT} sState = INIT;

void stepTick(){
    
    switch(sState){
      case INIT:
        if (xVal >= 400 && xVal <= 600){
          //transition
          sState = INIT;
          //action
          for (int i = 2; i < 6; i++){
            digitalWrite(i, LOW);
          }
        }
        else if (xVal > 600 ){
          sState = RIGHT;
        }
        else if (xVal < 400){
          sState = LEFT;
        }
        break;

      case LEFT:
        if (xVal < 400){
          //transition
          sState = LEFT;
          //action
          stepMotor.setSpeed(rolePerMinute);
          stepMotor.step(-50);
        }
        else if (xVal >= 400 ){
          sState = INIT;
        }
        else if (xVal > 600){
          sState = RIGHT;
        }
        break;

      case RIGHT:
        if (xVal > 600){
          //transition
          sState = RIGHT;
          //action
          stepMotor.setSpeed(rolePerMinute);
          stepMotor.step(50);
        }
        else if (xVal <=600){
          sState = INIT;
        }
        else if(xVal < 400)
        sState = LEFT;
        break;

      default:
      sState = INIT;
      break;
    }



}


//This formula i found online, i was not able to run the timer.h on a 1 microsecond cycle so i used delaymicroseconds
void distanceCalc(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cmDist = duration * 0.034 / 2;
  inchDist = duration * 0.0133 / 2;

}

void setup() {
  // put your setup code here, to run once:
  TimerSet(20);
  TimerOn();
  lcd.begin(16, 2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  stepMotor.setSpeed(rolePerMinute);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  xVal = analogRead(X_pin);
  stepTick();
  distanceCalc();
  Serial.print(xVal);
  Serial.print("\n");

  
  lcd.setCursor(0, 0); 
  lcd.print("Distance: "); 
  lcd.print(cmDist); 
  lcd.print(" cm    ");
  lcd.setCursor(0, 1);
  lcd.print("Distance: ");
  lcd.print(inchDist);
  lcd.print(" inch     ");





}
