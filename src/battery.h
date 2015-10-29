#ifndef BATTERY_H
#define BATTERY_H

namespace BFH
  {
    namespace Battery
      {
        void Init ();
        int GetBatteryPercentage ();

        void EmergencyShutdown ();
      }
  }


#endif /* end of include guard: BATTERY_H */
