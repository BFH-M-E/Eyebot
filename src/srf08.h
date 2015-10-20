#ifndef SRF08_H
#define SRF08_H

#include "arduino.h" /* for types  */

namespace BFH
  {
    enum
      {
        FrontLeft,
        FrontRight,
        SideLeft,
        Rear,
      };

    class SrfData
      {
      public:
        SrfData ();
        SrfData (int Range);
        SrfData (int Range, long Timestamp);

        int GetData ();
        long GetTimestamp ();

      private:
        int _Range;
        long _Timestamp;
      };

    class Srf08
      {
      public:
        Srf08 (byte Address);

        void StartMeasurement ();
        SrfData GetData ();

      private:
          byte _Address;
      };

    void InitSrf ();
    SrfData GetSrfData (int Name);
    const int MaxNumberOfSrfs = 4;
  }


#endif /* end of include guard: SRF08_H */
