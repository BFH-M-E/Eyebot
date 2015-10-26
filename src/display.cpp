#include "arduino.h"
#include "definitions.h"
#include "display.h"

#include "genieArduino/genieArduino.h"
#include "FreeRTOS/FreeRTOS_AVR.h"

namespace BFH
  {
    namespace Display
      {
        namespace
          {
            /* How many forms do exist?  */
            const int NumberOfForms = 6;
            int CurrentForm = 0;

            /* "State" - variables:
               There is a number of variables that can all contain either true
               or false. This variables states are changed by the buttons
               defined in the ButtonState(Re)SetButton constants  */
            const int NumberOfButtons = 4;
            bool ButtonState[NumberOfButtons] = {};
            const int ButtonStateSetButton[] =
              {
                FrmAufgabe1::BtnStart,  /* Frm1::BtnStart enables var 1  */
                FrmAufgabe2::BtnStart,  /* Frm2::...              var 2  */
                FrmAufgabe3::BtnStart,  /* ...                           */
                FrmAufgabe4::BtnStart,
              };
            const int ButtonStateResetButton[] =
              {
                FrmAufgabe1::BtnStop,  /* Frm1::BtnStop disables var 1  */
                FrmAufgabe2::BtnStop,  /* Frm2::...              var 2  */
                FrmAufgabe3::BtnStop,  /* ...                           */
                FrmAufgabe4::BtnStop,
              };

            /* "Counter" - variables:
               We want to keep track of some buttons number of pushes that have
               occured so far. The buttons to keep track of are defined in the
               ButtonPressCounterButton constant  */
            const int NumberOfButtonCounters = 8;
            int ButtonPresses[NumberOfButtonCounters] = {};
            const int ButtonPressCounterButton[] =
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

            /* Battery strings:
               There are a few different strings that show the current battery
               voltage. The BatteryString array defines those strings  */
            const int NumberOfBatteryStrings = 6;
            const int BatteryString [] =
              {
                FrmLanding::StrBattery,
                FrmAufgabe1::StrBattery,
                FrmAufgabe2::StrBattery,
                FrmAufgabe3::StrBattery,
                FrmAufgabe4::StrBattery,
                FrmPixy::StrBattery,
              };

            /* Battery containers:
               There are a few different "tanks" that show the current battery
               voltage. The BatteryTank array defines those "tanks"  */
            const int NumberOfBatteryTanks = 6;
            const int BatteryTank [] =
              {
                FrmLanding::TnkBattery,
                FrmAufgabe1::TnkBattery,
                FrmAufgabe2::TnkBattery,
                FrmAufgabe3::TnkBattery,
                FrmAufgabe4::TnkBattery,
                FrmPixy::TnkBattery,
              };

            /* Genie object instance  */
            Genie genie;

            /* Time (in [ms]) that the display needs to initialize  */
            const long InitTime = 5000;

            /* Variable to keep track of the time the display consumes
               to fully initialize itself  */
            long InitStartetAt = 0;
          }

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
            digitalWrite (DisplayResetPin, false);  /* Reset is low active!  */
            delay (100);
            digitalWrite (DisplayResetPin, true);   /* Reset is low active!  */

            /* Keep track of the time, at which the initialization of the
               display has started  */
            InitStartetAt = millis ();

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
            /* How long has it been, since the display startet it's
               initialization?  */
            long timeSinceInit = millis () - InitStartetAt;

            /* If it has not been at least as long as the display needs,
               wait time left  */
            if (timeSinceInit < InitTime)
              vTaskDelay (InitTime - timeSinceInit);

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

        int
        GetCurrentForm ()
          {
            return CurrentForm;
          }

        void
        ShowBatteryLevel (int Percentage)
          {
            if (Percentage < 0)   Percentage = 0;
            if (Percentage > 100) Percentage = 100;

            for (int i = 0; i < NumberOfForms; ++i)
              {
                genie.WriteObject (GENIE_OBJ_TANK, i, Percentage);
              }

            for (int i = 0; i < NumberOfBatteryStrings; ++i)
              {
                genie.WriteStr (BatteryString[i], Percentage);
              }
          }

        bool
        GetTaskState (int Task)
          {
            if (Task < 0 || Task > NumberOfButtons)
              return false;

            return ButtonState[Task];
          }

        int
        GetButtonPresses (int Button)
          {
            if (Button < 0 || Button > NumberOfButtonCounters)
              return 0;

            return ButtonPresses[Button];
          }
      }
  }
