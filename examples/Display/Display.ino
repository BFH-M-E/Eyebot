#include "Eyebot.h"

void
setup ()
  {
    Eyebot.Init (RobotColor::Red);
  }

void
loop ()
  {
    Serial.print (Eyebot.IsTask1Enabled ());
    Serial.print ("   ");

    Serial.print (Eyebot.IsTask2Enabled ());
    Serial.print ("   ");

    Serial.print (Eyebot.IsTask3Enabled ());
    Serial.print ("   ");

    Serial.print (Eyebot.IsTask4Enabled ());
    Serial.println ();

    for (int i = 1; i < 5; ++i)
      {
        Serial.print (Eyebot.GetButtonPresses (3, i));
        Serial.print (" ");
      }

    for (int i = 1; i < 5; ++i)
      {
        Serial.print (Eyebot.GetButtonPresses (4, i));
        Serial.print (" ");
      }

    Serial.println ();

    Serial.println (Eyebot.GetCurrentForm ());
  }
