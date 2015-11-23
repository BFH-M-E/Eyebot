#include "grabber.h"
#include "interruptlock.h"
#include "inline/Wire/Wire.h"

namespace BFH
  {
    namespace Grabber
      {
        namespace
          {
            int LiftAngle = 55;
            int GrabAngle = 45;
          }

        void
        Init ()
          {
            Wire.begin ();
          }

        void
        _SendAngles ()
          {
            Wire.beginTransmission (0x55);
            Wire.write (LiftAngle);
            Wire.write (GrabAngle);
            Wire.endTransmission ();
          }

        void
        SetLiftAngle (int Angle)
          {
            LiftAngle = Angle;

            _SendAngles ();
          }

        void
        SetGrabAngle (int Angle)
          {
            GrabAngle = Angle;

            _SendAngles ();
          }
      }
  }
