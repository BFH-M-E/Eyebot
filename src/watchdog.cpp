#include "watchdog.h"

namespace BFH
  {
    namespace Watchdog
      {
        void wdr ();

        void
        SetTimeout (Timeout timeout)
          {
            InterruptLock lock;

            WDTCSR |= (1 << WDCE) | (1 << WDE);
            WDTCSR = (1 << WDE) | timeout;
          }

        void
        Enable ()
          {
            InterruptLock lock;
            WDTCSR |= (1 << WDCE) | (1 << WDE);
            WDTCSR |= (1 << WDE);
          }

        void
        Disable ()
          {
            InterruptLock lock;
            wdr ();
            MCUSR &= ~(1 << WDRF);
            WDTCSR |= (1 << WDCE) | (1 << WDE);
            WDTCSR = 0x00;
          }

        void
        Reset ()
          {
            wdr ();
          }

        void
        TriggerSoftReset ()
          {
            InterruptLock lock;

            SetTimeout (MS_16);
            Enable ();

            while (1);
          }

        void
        wdr ()
          {
            asm volatile ("wdr");
          }

        __attribute__ ((constructor))
        void
        InitWatchdog ()
          {
            MCUSR &= ~WDRF;
            Watchdog::Disable ();
          }

      }
  }
