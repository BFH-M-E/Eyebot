#include "Eyebot.h"

void
setup ()
  {
    Eyebot.Init (RobotColor::Blue);
  }

void
loop ()
  {
    Eyebot.SetLed (Led1, true);
    Eyebot.SetLineSensorState (true);
    vTaskDelay (10);

    Eyebot.SetLed (Led1, false);
    Eyebot.SetLineSensorState (false);
    vTaskDelay (40);
  }
