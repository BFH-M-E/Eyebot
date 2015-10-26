#include "Eyebot.h"
#include "Wire.h"

#include "display.h"

void
setup ()
  {
    Eyebot.Init (RobotColor::Red);
  }

void
loop ()
  {
    Serial.println (Eyebot.GetButtonPresses (3, 2));

    delay (500);
  }
