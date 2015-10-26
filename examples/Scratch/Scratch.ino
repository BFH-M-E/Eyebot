#include <genieArduino.h>

Genie genie;

const int DisplayResetPin = 10;

void
DisplayEventHandler ()
  { }

void
setup ()
  {
    Serial3.begin (9600);

    /* Initialize display  */
    genie.Begin (Serial3);
    genie.AttachEventHandler (DisplayEventHandler);

    /* Reset display (this step is mandatory)  */
    pinMode (DisplayResetPin, OUTPUT);
    digitalWrite (DisplayResetPin, false);
    delay (100);
    digitalWrite (DisplayResetPin, true);
    delay (3500);
  }

  void
  SetBatteryLevel (int Percentage)
    {
      if (Percentage < 0)   Percentage = 0;
      if (Percentage > 100) Percentage = 100;

      for (int i = 0; i < 6; ++i)
        {
          genie.WriteObject (GENIE_OBJ_TANK, i, Percentage);
        }

      genie.WriteStr (0, Percentage);

    }

void
loop ()
  {
    genie.DoEvents();

    static long last = 0;
    if ((millis () - last) > 20)
      {
        static int p = 0;
        p += 3;
        p %= 100;
        SetBatteryLevel (p);

        last = millis ();
      }
  }
