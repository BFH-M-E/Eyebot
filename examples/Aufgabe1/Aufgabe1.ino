#include "Eyebot.h"

void
setup ()
  {
    /* Initialize Eyebot  */
    Eyebot.Init ();

    /* Code nach Eyebot.Init () wird nicht ausgeführt!  */
  }

int
TwoDimScanGetX ()
  {
    int d1 = Eyebot.GetSrfLeftValue ();
    int d2 = Eyebot.GetSrfRightValue ();

    int x = 0;

    // Algorithmus

    return x;
  }

int
TwoDimScanGetY ()
  {
    int d1 = Eyebot.GetSrfLeftValue ();
    int d2 = Eyebot.GetSrfRightValue ();

    int y = 0;

    // Algorithmus

    return y;
  }

void
loop ()
  {
    Serial.print (TwoDimScanGetX ());
    Serial.print ("   ");
    Serial.println (TwoDimScanGetY ());

    vTaskDelay (500);
  }
