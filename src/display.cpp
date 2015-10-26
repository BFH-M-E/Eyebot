#include "arduino.h"
#include "definitions.h"
#include "display.h"
#include "genieArduino/genieArduino.h"

namespace BFH
  {
    namespace Display
      {
        Genie genie;

        int CurrentForm = 0;
        bool ButtonState[NumberOfButtons] = {};

        int ButtonStateSetButton[] =
          {
            FrmAufgabe1::BtnStart,
            FrmAufgabe2::BtnStart,
            FrmAufgabe3::BtnStart,
            FrmAufgabe4::BtnStart,
          };

        int ButtonStateResetButton[] =
          {
            FrmAufgabe1::BtnStop,
            FrmAufgabe2::BtnStop,
            FrmAufgabe3::BtnStop,
            FrmAufgabe4::BtnStop,
          };

        /* Forward declaration  */
        void DisplayEventHandler ();

        void
        Init ()
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
Update ()
  {
    genie.DoEvents();
  }

        void
        DisplayEventHandler ()
          {
            genieFrame Event;
            genie.DequeueEvent (&Event);

            /* Check every possible GENIE_OBJ_FORM event, which is fired on
               form load and set the current state accordingly  */
            for (int i = 0; i < NumberOfForms; ++i)
              {
                /* If event number i happens, new state is i. See the enum in
                   namespace BFH::Display (display.h) to find the relation
                   between indices and actual forms  */
                if (genie.EventIs (&Event, GENIE_REPORT_EVENT, GENIE_OBJ_FORM, i))
                  CurrentForm = i;
              }

            /* There is an array containing some bools. Those bools get set on
               some buttons release event and reset on some OTHER buttons
               release event. The ButtonState(Re)SetButton arrays build the
               relation between indices and actual buttons. They are defined
               at the top of this file  */
            for (int i = 0; i < NumberOfButtons; ++i)
              {
                if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON,
                    ButtonStateSetButton[i]))
                  ButtonState[i] = true;

                else if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON,
                    ButtonStateResetButton[i]))
                  ButtonState[i] = false;
              }
          }

        bool
        GetButton (int Button)
          {
            if (Button < 0 || Button > NumberOfButtons)
              return false;

            return ButtonState[Button];
          }
      }
  }
