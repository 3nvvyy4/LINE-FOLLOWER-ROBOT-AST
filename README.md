# LINE-FOLLOWER-ROBOT-AST# LINE FOLLOWER ROBOT - AST

A line follower robot project developed for the AST competition.

## Hardware

Planned components:

- ESP32 DevKit V1
- TB6612FNG motor driver
- 2 DC motors
- QTR sensor array
- 2S LiPo battery 7.4V
- MPU6050 (possibly)
- 2 pin headers

## Software

- PlatformIO
- Arduino framework
- C++

## Current Progress

- [x] Created PlatformIO project
- [x] Implemented basic motor control logic
- [x] Added forward and backward motor direction control
- [x] Added PWM speed control
- [ ] Add QTR sensor
- [ ] Add QTR calibration
- [ ] Implement PID controller
- [ ] Combine PID with motor control
- [ ] Test on the physical robot

## Motor Control

The motors are controlled using:

```cpp
setMotors(leftSpeed, rightSpeed);
//example:
//setMotors(100, 100);   // Forward
//setMotors(-100, -100); // Backward
//setMotors(100, 50);    // Curve right
//setMotors(50, 100);    // Curve left
```
## Project Structure:
src/
    main.cpp

platformio.ini
README.md
