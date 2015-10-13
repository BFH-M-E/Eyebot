#ifndef DEFINITIONS_H
#define DEFINITIONS_H

/* ==========     Limits     ==========  */
const float BatteryCutoffVoltage = 11.0f;


/* ==========     Pins     ==========  */

/* Propulsion  */
const int TailWheelServoPin = 29;

const int Pwm1APin = 8;
const int Pwm1BPin = 9;
const int Pwm1ENPin = 5;

const int Pwm2APin = 11;
const int Pwm2BPin = 12;
const int Pwm2ENPin = 6;

const int Encoder1APin = 19;
const int Encoder1BPin = 18;
const int Encoder2APin = 2;
const int Encoder2BPin = 3;


/* User interface  */
const int Button1Pin = 24;
const int Button2Pin = 25;
const int Button3Pin = 26;
const int Led1Pin = 44;
const int Led2Pin = 45;
const int Led3Pin = 46;

/* Sensors  */
const int LineSensorEnablePin = 49;
const int LineSensor1Pin = 0;
const int LineSensor2Pin = 1;
const int LineSensor3Pin = 2;
const int LineSensor4Pin = 7;

/* Peripherals  */
const int Servo1Pin = 29;
const int Servo2Pin = 28;
const int Servo3Pin = 30;
const int Servo4Pin = 31;
const int Servo5Pin = 32;
const int Servo6Pin = 33;

/* Power management  */
const int BatteryPin = 15;
const int TracoEnablePin = 38;

#endif /* end of include guard: DEFINITIONS_H */
