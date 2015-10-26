#ifndef DISPLAY_H
#define DISPLAY_H

namespace BFH
  {
    namespace Display
      {
        enum
          {
            Splash,
            Aufgabe1,
            Aufgabe2,
            Aufgabe3,
            Aufgabe4,
            BatteryWarning,
            // Pixy,
          };

        namespace FrmSplash
          {
            enum
              {
                BtnAufgabe1,
                BtnAufgabe2,
                BtnAufgabe3,
                BtnAufgabe4,
              };
          }

        namespace FrmAufgabe1
          {
            enum
              {
                BtnStart,
                BtnStop,
                BtnZuruck,
              };
          }

        namespace FrmAufgabe2
          {
            enum
              {
                BtnStart,
                BtnStop,
                BtnZuruck,
              };
          }

        namespace FrmAufgabe3
          {
            enum
              {
                BtnStart,
                BtnStop,
                BtnZuruck,
              };
          }

        namespace FrmAufgabe4
          {
            enum
              {
                BtnStart,
                BtnStop,
                BtnZuruck,
              };
          }

        namespace FrmBatteryWarning
          {

          }

        namespace FrmPixy
          {
            enum
              {
                BtnStart,
                BtnStop,
                BtnZuruck,
              };
          }
      }

    namespace Display
      {
        void Init ();

void Update ();

        void ShowForm (int Form);
        bool GetButton (int Button);
        void Print ();

        const int NumberOfForms = 6;
        const int NumberOfButtons = 4;

        extern int CurrentForm;
      }
  }


#endif /* end of include guard: DISPLAY_H */
