#ifndef DISPLAY_H
#define DISPLAY_H

namespace BFH
  {
    namespace Display
      {
        enum
          {
            Landing = 0,
            Aufgabe1 = 1,
            Aufgabe2 = 2,
            Aufgabe3 = 3,
            Aufgabe4 = 4,
            BatteryWarning = 5,
            // Pixy = 6,
          };

        namespace FrmSplash
          {
            enum
              {
                BtnAufgabe1 = 0,
                BtnAufgabe2 = 1,
                BtnAufgabe3 = 2,
                BtnAufgabe4 = 3,
              };
          }

        namespace FrmAufgabe1
          {
            enum
              {
                BtnStart = 5,
                BtnStop = 6,
                BtnZuruck = 4,
              };
          }

        namespace FrmAufgabe2
          {
            enum
              {
                BtnStart = 8,
                BtnStop = 7,
                BtnZuruck = 9,
              };
          }

        namespace FrmAufgabe3
          {
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
          }

        namespace FrmAufgabe4
          {
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
          }

        namespace FrmBatteryWarning
          {

          }

        namespace FrmPixy
          {
            enum
              {
                BtnStart = 24,
                BtnStop = 25,
                BtnZuruck = 26,
              };
          }
      }

    namespace Display
      {
        void Init ();

        void ShowForm (int Form);
        bool GetTaskState (int Task);
        int GetButtonPresses (int Index);

        const int NumberOfForms = 6;
        const int NumberOfButtons = 4;
        const int NumberOfButtonCounters = 8;

        extern int CurrentForm;
      }
  }


#endif /* end of include guard: DISPLAY_H */
