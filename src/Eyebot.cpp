#include "arduino.h"
#include "battery.h"
#include "definitions.h"
#include "propulsion.h"
#include "srf08.h"
#include "Wire.h"

#include "Eyebot.h"
#include "RTOS.h"

namespace BFH
  {
    float BatteryVoltage = 0.0f;

    void
    Eyebot::Init (int Color)
      {
        this->Color = Color;

        Serial.begin (9600);
        Wire.begin ();

        /* User interface  */
        pinMode (Button1Pin, INPUT);
        pinMode (Button2Pin, INPUT);
        pinMode (Button3Pin, INPUT);
        pinMode (Led1Pin, OUTPUT);
        pinMode (Led2Pin, OUTPUT);
        pinMode (Led3Pin, OUTPUT);

        /* Traco enable  */
        pinMode (TracoEnablePin, OUTPUT);

        /* Sensors  */
        pinMode (LineSensorEnablePin, OUTPUT);

        InitPropulsion ();
        InitSrf ();
        InitBatteryChecker ();

        InitRtos ();
      }

    void
    Eyebot::SetLed (int Led, bool Value)
      {
        if (Value)
          SetLed (Led, 255);
        else
          SetLed (Led, 0);
      }

    void
    Eyebot::SetLed (int Led, int Value)
      {
        /* Limit parameter range  */
        if (Value < 0)    Value = 0;
        if (Value > 255)  Value = 255;

        switch (Led)
          {
          case Led1:
            analogWrite (Led1Pin, Value);
            break;

          case Led2:
            analogWrite (Led2Pin, Value);
            break;

          case Led3:
            analogWrite (Led3Pin, Value);
            break;

          default:
            break;
          }
      }

    void
    Eyebot::SetTracoState (bool State)
      {
        digitalWrite (TracoEnablePin, State);
      }

    void
    Eyebot::SetLineSensorState (bool State)
      {
        digitalWrite (LineSensorEnablePin, State);
      }

    bool
    Eyebot::GetButton (int Button)
      {
        bool state = false;

        switch (Button)
          {
          case Button1:
            state = digitalRead (Button1Pin);
            break;

          case Button2:
            state = digitalRead (Button2Pin);
            break;

          case Button3:
            state = digitalRead (Button3Pin);
            break;

          default:
            break;
          }

        return state;
      }

    int
    Eyebot::GetLineSensor (int Sensor)
      {
        int value;

        switch (Sensor)
          {
          case LineSensor1:
            value = analogRead (LineSensor1Pin);
            break;

          case LineSensor2:
            value = analogRead (LineSensor2Pin);
            break;

          case LineSensor3:
            value = analogRead (LineSensor3Pin);
            break;

          default:
            break;
          }

        return value;
      }

    float
    Eyebot::GetBatteryVoltage ()
      {
        /* Read battery voltage value  */
        int batteryValue = analogRead (BatteryPin);

        /* The voltage reference is made by the Arduino MEGA board's 5 V voltage
           regulator. Therefore, we can assume 5.0 V as reference  */
        float analogVoltage = batteryValue * 5.0f / 1023.0f;

        /* Conversion factor to trim the voltage divider (there should be no need
           to change this value, as long as 1 % resistors are used, as they produce a
           total error of less than 1.5 %)  */
        float batteryVoltage = analogVoltage / 0.3125f;

        return batteryVoltage;
      }

    int
    Eyebot::GetBatteryPercent ()
      {
        /* Limit voltage  */
        float result = BatteryVoltage;
        if (result > BatteryFullVoltage)
          result = BatteryFullVoltage;
        if (result < BatteryEmptyVoltage)
          result = BatteryEmptyVoltage;

        /* Convert to percent  */
        result -= BatteryEmptyVoltage;
        result *= 100;
        result /= (BatteryFullVoltage - BatteryEmptyVoltage);

        return static_cast<int> (result);
      }

    int
    Eyebot::GetSrfLeftValue ()
      {
        return GetSrfData (FrontLeft).GetData ();
      }

    int
    Eyebot::GetSrfRightValue ()
      {
        return GetSrfData (FrontRight).GetData ();
      }

    int
    Eyebot::GetSrfSideValue ()
      {
        return GetSrfData (SideLeft).GetData ();
      }

    int
    Eyebot::GetSrfBackValue ()
      {
        return GetSrfData (Rear).GetData ();
      }

    void
    Eyebot::Stop ()
      {
        ::Stop ();
      }

    void
    Eyebot::SetMotorState (bool State)
      {
        if (State)
          EnableMotors ();
        else
          DisableMotors ();
      }

    void
    Eyebot::SetForwardSpeed (float Speed)
      {
        ::SetForwardSpeed (Speed);
      }

    void
    Eyebot::SetTailWheelAngle (int AngleInDegree)
      {
        ::SetTailWheelAngle (AngleInDegree);
      }
  }

BFH::Eyebot Eyebot;
