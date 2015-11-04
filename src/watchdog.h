#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "interruptlock.h"

namespace BFH
  {
    namespace Watchdog
      {
        /* Timeout timings in milliseconds  */
        enum Timeout
          {
            MS_16 =   (0 << WDP3) | (0 << WDP2) | (0 << WDP1) | (0 << WDP0),
            MS_32 =   (0 << WDP3) | (0 << WDP2) | (0 << WDP1) | (1 << WDP0),
            MS_64 =   (0 << WDP3) | (0 << WDP2) | (1 << WDP1) | (0 << WDP0),
            MS_125 =  (0 << WDP3) | (0 << WDP2) | (1 << WDP1) | (1 << WDP0),
            MS_250 =  (0 << WDP3) | (1 << WDP2) | (0 << WDP1) | (0 << WDP0),
            MS_500 =  (0 << WDP3) | (1 << WDP2) | (0 << WDP1) | (1 << WDP0),
            MS_1000 = (0 << WDP3) | (1 << WDP2) | (1 << WDP1) | (0 << WDP0),
            MS_2000 = (0 << WDP3) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0),
            MS_4000 = (1 << WDP3) | (0 << WDP2) | (0 << WDP1) | (0 << WDP0),
            MS_8000 = (1 << WDP3) | (0 << WDP2) | (0 << WDP1) | (1 << WDP0),
          };

        void SetTimeout (Timeout timeout);

        void Enable ();
        void Disable ();
        void Reset ();

        void TriggerSoftReset ();
      }
  }

  #endif /* end of include guard: WATCHDOG_H */
