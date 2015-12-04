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
        Red,
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
        void Init ();

        void SetLed (int Led, bool State);
        void SetLed (int Led, int Value);
        void SetTracoState (bool State);
        void SetLineSensorState (bool State);

        bool GetButton (int Button);
        int GetLineSensor (int Sensor);
        float GetBatteryVoltage ();

        int GetSrfLeftValue ();
        int GetSrfRightValue ();
        int GetSrfSideValue ();
        int GetSrfBackValue ();

        /* Display  */
        int GetCurrentForm ();
        bool IsTask1Enabled ();
        bool IsTask2Enabled ();
        bool IsTask3Enabled ();
        bool IsTask4Enabled ();
        int GetButtonPresses (int Form, int Button);
        void SetDisplayString (int Identifier, int Value);

        void Stop ();

        void SetMotorState (bool State);

        void SetSpeed (int Speed);
        void SetSpeed (float Speed);
        void SetTailWheelAngle (int AngleInDegree);

        float GetDrivenDistance ();
        float GetEncoderValueLeft ();
        float GetEncoderValueRight ();

        /* "Greifer Plugin"  */
        void SetGrabberLiftAngle (int Angle);
        void SetGrabberGrabAngle (int Angle);

        /* "Laser Plugin" */
        void SetLaserPanAngle (int Angle);
        void SetLaserTiltAngle (int Angle);
        void EnableLaser ();
        void DisableLaser ();

		int PS4JoystickLeftX();
        int PS4JoystickLeftY();
        int PS4JoystickRightX();
        int PS4JoystickRightY();
      };
  }

extern BFH::Eyebot Eyebot;

#endif /* end of include guard: EYEBOT_H */
