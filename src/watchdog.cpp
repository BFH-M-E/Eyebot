#include "watchdog.h"

void
Watchdog::SetTimeout (Timeout timeout)
  {
    InterruptLock lock;

    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = (1 << WDE) | timeout;
  }

void
Watchdog::Enable ()
  {
    InterruptLock lock;
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR |= (1 << WDE);
  }

void
Watchdog::Disable ()
  {
    InterruptLock lock;
    _wdr ();
    MCUSR &= ~(1 << WDRF);
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = 0x00;
  }

void
Watchdog::Reset ()
  {
    _wdr ();
  }

void
Watchdog::_wdr ()
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
