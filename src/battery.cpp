#include "arduino.h"
#include "battery.h"
#include "display.h"
#include "definitions.h"
#include "interruptlock.h"

#include "FreeRTOS/FreeRTOS_AVR.h"

namespace BFH
  {
    namespace Battery
      {
        namespace
          {
            /* Battery limits  */
            const float BatteryEmptyVoltage = 10.0f;
            const float BatteryFullVoltage = 12.3f;

            const int BatteryWarningPercentage = 10;

            int BatteryPercentage = 0;
          }

        void
        BatteryCheckTask (void* param)
          {
            while (1)
              {
                /* Read battery voltage value  */
                int batteryValue = analogRead (BatteryPin);

                /* The voltage reference is made by the Arduino MEGA board's 5 V voltage
                   regulator. Therefore, we can assume 5.0 V as reference  */
                float analogVoltage = batteryValue * 5.0f / 1023.0f;

                /* Conversion factor to trim the voltage divider (there should be no need
                   to change this value, as long as 1 % resistors are used, as they produce a
                   total error of less than 1.5 %)  */
                float newBatteryVoltage = analogVoltage / 0.3125f;

                static float BatteryVoltage = newBatteryVoltage;

                /* Low pass  */
                float alpha = 0.3;  /* Higher value leads to faster convergence  */
                BatteryVoltage *= (1 - alpha);
                BatteryVoltage += alpha * newBatteryVoltage;

                /* Limit voltage  */
                float result = BatteryVoltage;
                if (result > BatteryFullVoltage)
                  result = BatteryFullVoltage;
                if (result < BatteryEmptyVoltage)
                  result = BatteryEmptyVoltage;

                /* Convert to percent  */
                result -= BatteryEmptyVoltage;
                result *= 100;
                result /= (BatteryFullVoltage - BatteryEmptyVoltage);
                BatteryPercentage = static_cast<int> (result);

                Display::ShowBatteryLevel (BatteryPercentage);

                /* Show warning screen if battery voltage drops too low  */
                if (BatteryPercentage < BatteryWarningPercentage)
                  {
                    if (Display::GetCurrentForm () != Display::BatteryWarning)
                      Display::ShowForm (Display::BatteryWarning);
                  }

                /* Low voltage cutoff  */
                if (BatteryVoltage < BatteryEmptyVoltage)
                  {
                    EmergencyShutdown ();
                  }

                vTaskDelay (1000);
              }
          }

        void
        Init ()
          {
            if (xTaskCreate (BatteryCheckTask, NULL, 512, NULL, 3, NULL) != pdPASS)
              {
                Serial.println (F ("ERROR: TaskCreate: BatteryCheckTask"));
                while (1);
              }
          }

        int
        GetBatteryPercentage ()
          {
            return BatteryPercentage;
          }

        void
        EmergencyShutdown ()
          {
            InterruptLock lock;

            digitalWrite (TracoEnablePin, false);
            digitalWrite (Led1Pin, true);
            digitalWrite (Led2Pin, false);
            digitalWrite (Led3Pin, false);

            while (1);
          }
      }
  }
