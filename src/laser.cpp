#include "laser.h"
#include "inline/Wire/Wire.h"

namespace BFH
  {
    namespace Laser
      {
        namespace
          {
            uint8_t PanAngle = 90;
            uint8_t TiltAngle = 90;
            uint8_t Flags = 0x00;
          }

        void
        Init ()
          {
            Wire.begin ();
          }

        void
        _SendData ()
          {
            Wire.beginTransmission (0x60);
            Wire.write (PanAngle);
            Wire.write (TiltAngle);
            Wire.write (Flags);
            Wire.endTransmission ();
          }

        void
        SetPanAngle (int Angle)
          {
            PanAngle = Angle;

            _SendData ();
          }

        void
        SetTiltAngle (int Angle)
          {
            TiltAngle = Angle;

            _SendData ();
          }

        void
        EnableLaser ()
          {
            Flags = 0x01;

            _SendData ();
          }

        void
        DisableLaser ()
          {
            Flags = 0x00;

            _SendData ();
          }
      }
  }
