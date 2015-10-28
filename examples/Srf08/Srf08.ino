#include "Eyebot.h"

void
setup ()
  {
    /* Initialize Eyebot  */
    Eyebot.Init (RobotColor::Blue);
  }

void
loop ()
  {
    Serial.print (Eyebot.GetSrfLeftValue ());
    Serial.print ("   ");

    Serial.print (Eyebot.GetSrfRightValue ());
    Serial.print ("   ");

    Serial.print (Eyebot.GetSrfSideValue ());
    Serial.print ("   ");

    Serial.print (Eyebot.GetSrfBackValue ());
    Serial.print ("   ");

    Serial.println ();
  }
