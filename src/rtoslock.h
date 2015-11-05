#ifndef RTOSLOCK_H
#define RTOSLOCK_H

#include "FreeRTOS/FreeRTOS_AVR.h"

namespace BFH
  {
    class RtosLock
      {
      public:
        RtosLock ()  { vTaskSuspendAll (); }
        ~RtosLock () { xTaskResumeAll (); }
      };
  }

#endif /* end of include guard: RTOSLOCK_H */
