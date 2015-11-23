#ifndef PS4_H
#define PS4_H

#include "arduino.h" /* for types  */

namespace BFH
  {
    namespace PS4
      {
        void Init();
        int GetJoystickLeftX ();
        int GetJoystickLeftY ();
        int GetJoystickRightX ();
        int GetJoystickRightY ();
      }
  }


#endif /* end of include guard: SRF08_H */
