#ifndef LASER_H
#define LASER_H

namespace BFH
  {
    namespace Laser
      {
        void Init ();

        void SetPanAngle (int Angle);
        void SetPanAngle (float Angle);
        void SetTiltAngle (int Angle);
        void SetTiltAngle (float Angle);
        void EnableLaser ();
        void DisableLaser ();
      }
  }

#endif /* end of include guard: LASER_H */
