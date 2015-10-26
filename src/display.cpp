#include "arduino.h"
#include "definitions.h"
#include "display.h"

#include "genieArduino/genieArduino.h"
#include "FreeRTOS/FreeRTOS_AVR.h"

namespace BFH
  {
    namespace Display
      {
        Genie genie;

        int CurrentForm = 0;
        bool ButtonState[NumberOfButtons] = {};
        int ButtonPresses[NumberOfButtonCounters] = {};

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

        int ButtonPressCounterButton[] =
          {
            FrmAufgabe3::BtnUser1,
            FrmAufgabe3::BtnUser2,
            FrmAufgabe3::BtnUser3,
            FrmAufgabe3::BtnUser4,
            FrmAufgabe4::BtnUser1,
            FrmAufgabe4::BtnUser2,
            FrmAufgabe4::BtnUser3,
            FrmAufgabe4::BtnUser4,
          };

        /* Forward declaration  */
        void DisplayEventHandler ();
        void DisplayTask (void* param);

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

            /* Init display task  */
            if (xTaskCreate (DisplayTask, NULL, 256, NULL, 2, NULL) != pdPASS)
              {
                Serial.println (F ("ERROR: TaskCreate: DisplayTask"));
                while (1);
              }
          }

        void
        DisplayTask (void* param)
          {
            while (1)
              {
                /* Request display events  */
                genie.DoEvents();

                /* Sampling the events at 200 Hz should be enough  */
                vTaskDelay (5);
              }
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
                  {
                    /* Set all tasks buttons state to false (e.g. let the
                       user programm think, the "Stop" button was pressed)  */
                    for (int j = 0; j < NumberOfButtons; ++j)
                      ButtonState[j] = false;

                    CurrentForm = i;
                  }
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

            /* For some of the buttons, the user cares for how many times they
               have been pressed since the application was started. Therefore
               we have an array that builds the relation between the indices
               and the actual buttons. This array is defined at the top of
               this file  */
            for (int i = 0; i < NumberOfButtonCounters; ++i)
              {
                if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON,
                    ButtonPressCounterButton[i]))
                  ButtonPresses[i]++;
              }

          }

        void
        ShowForm (int Form)
          {
            if (Form < 0 || Form > NumberOfForms)
              return;

            genie.WriteObject (GENIE_OBJ_FORM, Form, 0);
          }

        bool
        GetTaskState (int Task)
          {
            if (Task < 0 || Task > NumberOfButtons)
              return false;

            return ButtonState[Task];
          }

        int
        GetButtonPresses (int Index)
          {
            if (Index < 0 || Index > NumberOfButtonCounters)
              return 0;

            return ButtonPresses[Index];
          }
      }
  }
