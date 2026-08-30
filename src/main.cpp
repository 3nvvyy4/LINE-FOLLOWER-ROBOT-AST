#include <Arduino.h>

//=======================
// ROBOT SETUP
//=======================

//-------------------------
//-----TB6612FNG Motor Driver-----
//-------------------------
// left motor
const int AIN1 = NULL;
const int AIN2 = NULL;
const int PWMA = NULL;

// right motor
const int BIN1 = NULL;
const int BIN2 = NULL;
const int PWMB = NULL;
//stand by
const int STBY = NULL;
//We'll setup the other components when we get the design

//setMotors function that makes the motors work
void setMotors(int leftspeed, int rightspeed){
  leftspeed = constrain(leftspeed, -255, 255);
  rightspeed = constrain(rightspeed, -255, 255);
  //adjusting directions
  if(leftspeed > 0){
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  }else if(leftspeed < 0){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    leftspeed = leftspeed * -1;
  }else{
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
  }

  if(rightspeed > 0){
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }else if(rightspeed < 0){
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    rightspeed = rightspeed * -1;
  }else{
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
  //adjusting speed
  analogWrite(PWMA, leftspeed);
  analogWrite(PWMB, rightspeed);
}
void setup() {
  //setup the pins for the motors
  //left motor
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  //right motor
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  //standby pin
  pinMode(STBY, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}

