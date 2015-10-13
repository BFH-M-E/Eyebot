#include "Eyebot.h"

void
setup ()
{
  Eyebot.Init ();
}

void
loop ()
{
  if (Eyebot.GetBatteryVoltage () < 11.0f)
    {
      Eyebot.SetTracoState (false);
      delay (1000);
    }
  else
    {
      Eyebot.SetTracoState (true);
    }

  Eyebot.SetForwardSpeed (0.05f);

  if (Eyebot.GetButton (Button1))
    Eyebot.SetMotorState (true);

  if (Eyebot.GetButton (Button2))
    Eyebot.SetMotorState (false);

  Eyebot.SetTailWheelAngle (0);

  delay (100);
}
