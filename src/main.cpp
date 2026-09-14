#include <Arduino.h>
//=======================
// 8-SENSOR LINE FOLLOWER
//=======================

// -1: Replace these with the real ESP32 GPIO pins
const int sensorPins[8] = {
    -1, -1, -1, -1,
    -1, -1, -1, -1
};

// Sensor weights: left → right
const int sensorWeights[8] = {
    -7, -5, -3, -1,
     1,  3,  5,  7
};

// PID parameters
float Kp = 20.0;
float Ki = 0.0;
float Kd = 10.0;

float previousError = 0;
float integral = 0;

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
//=======================
// READ LINE POSITION
//=======================

float readLine() {
    long weightedSum = 0;
    int activeSensors = 0;

    for (int i = 0; i < 8; i++) {
        // TODO: This will work after we choose the real GPIO pins
        int sensorValue = digitalRead(sensorPins[i]);

        // Assumption: sensor outputs LOW when it detects the black line
        if (sensorValue == LOW) {
            weightedSum += sensorWeights[i];
            activeSensors++;
        }
    }

    // If no sensor detects the line,
    // keep the previous error instead of jumping randomly.
    if (activeSensors == 0) {
        return previousError;
    }

    return (float)weightedSum / activeSensors;
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

    // Read the position of the line
    float error = readLine();

    //=======================
    // PID CALCULATION
    //=======================

    // Proportional
    float P = error;

    // Integral
    integral += error;

    // Prevent integral from becoming too large
    integral = constrain(integral, -100, 100);

    // Derivative
    float D = error - previousError;

    // PID correction
    float correction = (Kp * P) + (Ki * integral) + (Kd * D);

    //=======================
    // MOTOR SPEED
    //=======================

    const int baseSpeed = 150;

    int leftSpeed = baseSpeed + correction;
    int rightSpeed = baseSpeed - correction;

    // Keep speeds inside motor limits
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);

    // Send speeds to the motors
    setMotors(leftSpeed, rightSpeed);

    // Save current error for next loop
    previousError = error;

    delay(5);
}


 
 