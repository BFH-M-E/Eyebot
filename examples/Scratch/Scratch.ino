#include "Eyebot.h"
#include "display.h"
void
setup ()
  {
    Eyebot.Init (RobotColor::Blue);
  }

void
loop ()
  {
    int L = Eyebot.GetSrfLeftValue ();
    int R = Eyebot.GetSrfRightValue ();

    Eyebot.SetDisplayString (BFH::Display::FrmAufgabe1::StrL, L);
    Eyebot.SetDisplayString (BFH::Display::FrmAufgabe1::StrR, R);

    float l = static_cast<float>(L) / 1000.0f;
    float r = static_cast<float>(R) / 1000.0f;

    float s = 0.0665f;
    float ss = 2 * s;

    int x = ((pow (l, 2) - pow (r, 2)) / (4 * s)) * 1000;
    int y = sqrt ((r + ss + l) * (r - ss + l) * (r + ss - l) * (-r + ss + l))
        / (4 * s) * 1000;

    Eyebot.SetDisplayString (BFH::Display::FrmAufgabe1::StrX, x);
    Eyebot.SetDisplayString (BFH::Display::FrmAufgabe1::StrY, y);

    vTaskDelay (300);
  }
