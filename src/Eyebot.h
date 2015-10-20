#ifndef EYEBOT_H
#define EYEBOT_H

#include "FreeRTOS/FreeRTOS_AVR.h"

enum Led
  {
    Led1,
    Led2,
    Led3,
  };

enum Button
  {
    Button1,
    Button2,
    Button3,
  };

enum LineSensor
  {
    LineSensor1,
    LineSensor2,
    LineSensor3,
    LineSensor4,
  };

namespace RobotColor
  {
    enum Color
      {
        Green,
        Blue,
        Black,
        Gold,
      };
  }

namespace BFH
  {
    extern float BatteryVoltage;

    class Eyebot
      {
      public:
        void Init (int Color);

        void SetLed (int Led, bool State);
        void SetLed (int Led, int Value);
        void SetTracoState (bool State);
        void SetLineSensorState (bool State);

        bool GetButton (int Button);
        int GetLineSensor (int Sensor);
        float GetBatteryVoltage ();
        int GetBatteryPercent ();

        int GetSrfLeftValue ();
        int GetSrfRightValue ();
        int GetSrfSideValue ();
        int GetSrfBackValue ();

        void Stop ();

        void SetMotorState (bool State);

        void SetForwardSpeed (float Speed);
        void SetTailWheelAngle (int AngleInDegree);

        int Color;
      };
  }

extern BFH::Eyebot Eyebot;

#endif /* end of include guard: EYEBOT_H */
