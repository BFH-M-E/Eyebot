#ifndef DISPLAY_H
#define DISPLAY_H

namespace BFH
  {
    namespace Display
      {
        /* Forms  */
        enum
          {
            Landing = 0,
            Aufgabe1 = 1,
            Aufgabe2 = 2,
            Aufgabe3 = 3,
            Aufgabe4 = 4,
            Pixy = 5,
            BatteryWarning = 6,
          };

        namespace FrmLanding
          {
            /* Buttons  */
            enum
              {
                BtnAufgabe1 = 0,
                BtnAufgabe2 = 1,
                BtnAufgabe3 = 2,
                BtnAufgabe4 = 3,
              };

            /* Strings  */
            enum
              {
                StrBattery = 0,
              };

            /* Battery container "Tank"  */
            enum
              {
                TnkBattery = 0,
              };
          }

        namespace FrmAufgabe1
          {
            /* Buttons  */
            enum
              {
                BtnStart = 5,
                BtnStop = 6,
                BtnZuruck = 4,
              };

            /* Strings  */
            enum
              {
                StrBattery = 1,
                StrL = 2,
                StrR = 3,
                StrX = 4,
                StrY = 5,
              };

            /* Battery container "Tank"  */
            enum
              {
                TnkBattery = 1,
              };
          }

        namespace FrmAufgabe2
          {
            /* Buttons  */
            enum
              {
                BtnStart = 8,
                BtnStop = 7,
                BtnZuruck = 9,
              };

            /* Strings  */
            enum
              {
                StrBattery = 6,
              };

            /* Battery container "Tank"  */
            enum
              {
                TnkBattery = 2,
              };
          }

        namespace FrmAufgabe3
          {
            /* Buttons  */
            enum
              {
                BtnStart = 10,
                BtnStop = 11,
                BtnZuruck = 12,
                BtnUser1 = 14,
                BtnUser2 = 16,
                BtnUser3 = 13,
                BtnUser4 = 15,
              };

            /* Strings  */
            enum
              {
                StrBattery = 7,
                StrUser1 = 10,
                StrUser2 = 11,
                StrUser3 = 8,
                StrUser4 = 9,
              };

            /* Battery container "Tank"  */
            enum
              {
                TnkBattery = 3,
              };
          }

        namespace FrmAufgabe4
          {
            /* Buttons  */
            enum
              {
                BtnStart = 19,
                BtnStop = 17,
                BtnZuruck = 18,
                BtnUser1 = 20,
                BtnUser2 = 21,
                BtnUser3 = 22,
                BtnUser4 = 23,
              };

            /* Strings  */
            enum
              {
                StrBattery = 12,
                StrUser1 = 13,
                StrUser2 = 14,
                StrUser3 = 15,
                StrUser4 = 16,
              };

            /* Battery container "Tank"  */
            enum
              {
                TnkBattery = 4,
              };
          }

        namespace FrmBatteryWarning
          {
            /* Battery container "Tank"  */
            enum
              {
                TnkBattery = 6,
              };
          }

        namespace FrmPixy
          {
            /* Buttons  */
            enum
              {
                BtnStart = 24,
                BtnStop = 25,
                BtnZuruck = 26,
              };

            /* Strings  */
            enum
              {
                StrBattery = 17,
              };

            /* Battery container "Tank"  */
            enum
              {
                TnkBattery = 5,
              };
          }
      }

    namespace Display
      {
        void Init ();

        void ShowForm (int Form);
        int GetCurrentForm ();

        void ShowBatteryLevel (int Percentage);

        bool GetSoftSwitchState (int Task);
        int GetButtonPresses (int Button);
      }
  }


#endif /* end of include guard: DISPLAY_H */
