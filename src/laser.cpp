#include "laser.h"
#include "inline/Wire/Wire.h"

namespace BFH
  {
    namespace Laser
      {
        namespace
          {
            float PanAngle = 90.0f;
            float TiltAngle = 90.0f;
            uint8_t Flags = 0x00;
          }

        void
        Init ()
          {
            Wire.begin ();
          }

        union FloatBuffer
          {
            /* We use a union to cast types here. This is undefined behavior
               in c++. Most compilers do however support this (and it works)
               for us  */

            float f;
            uint8_t c[4];
          };

        void
        _SendData ()
          {
            /* We use a union to cast types here. This is undefined behavior
               in c++. Most compilers do however support this (and it works)
               for us  */
            FloatBuffer floatBuffer;

            Wire.beginTransmission (0x60);

            /* Transmit pan angle  */
            floatBuffer.f = PanAngle;
            Wire.write (floatBuffer.c, 4);

            /* Transmit tilt angle  */
            floatBuffer.f = TiltAngle;
            Wire.write (floatBuffer.c, 4);

            /* Transmit flags  */
            Wire.write (Flags);

            Wire.endTransmission ();

            // Wire.beginTransmission (0x60);
            // Wire.write (PanAngle);
            // Wire.write (TiltAngle);
            // Wire.write (Flags);
            // Wire.endTransmission ();
          }

        void
        SetPanAngle (int Angle)
          {
            SetPanAngle (static_cast<float> (Angle));
          }

        void
        SetPanAngle (float Angle)
          {
            PanAngle = Angle;

            _SendData ();
          }

        void
        SetTiltAngle (int Angle)
          {
            SetTiltAngle (static_cast<float> (Angle));
          }

        void
        SetTiltAngle (float Angle)
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
