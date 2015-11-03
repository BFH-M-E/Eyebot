#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "interruptlock.h"

class Watchdog
  {
  public:
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

    static void SetTimeout (Timeout timeout);
    static void Enable ();
    static void Disable ();
    static void Reset ();

  private:
    static void inline _wdr ();
  };

  #endif /* end of include guard: WATCHDOG_H */
