#ifndef SRF08_H
#define SRF08_H

namespace Srf
  {
    enum SrfNumber
      {
        FrontLeft,
        FrontRight,
        SideLeft,
        Rear,
      };
  }

namespace BFH
  {
    class Srf08
      {
      public:
        Srf08 (byte Address);
        int GetDistance ();

        byte I2cAddress;
        byte Distance;
      };

    void InitSrf ();
    int GetSrfDistance (int Srf);
  }

#endif /* end of include guard: SRF08_H */
