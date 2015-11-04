#ifndef INTERRUPTLOCK_H
#define INTERRUPTLOCK_H

#include <avr/interrupt.h>

namespace BFH
  {
    class InterruptLock
      {
      public:
        InterruptLock ()  { cli(); }
        ~InterruptLock () { sei (); }
      };
  }

  #endif /* end of include guard: INTERRUPTLOCK_H */
