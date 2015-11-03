#include <avr/interrupt.h>

class InterruptLock
  {
  public:
    InterruptLock ()  { cli(); }
    ~InterruptLock () { sei (); }
  };
