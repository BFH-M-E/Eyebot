#include "arduino.h"
#include "battery.h"
#include "display.h"
#include "definitions.h"
#include "Eyebot.h"

#include "FreeRTOS/FreeRTOS_AVR.h"

namespace BFH
  {
    int BatteryPercentage = 0;

    void
    BatteryCheckTask (void* param)
      {
        /* Initialize global variable  */
        BatteryVoltage = ::Eyebot.GetBatteryVoltage ();

        while (1)
          {
            /* Read current battery voltage  */
            float voltage = ::Eyebot.GetBatteryVoltage ();

            /* Low pass  */
            float alpha = 0.3;  /* Higher value leads to faster convergation  */
            BatteryVoltage *= (1 - alpha);
            BatteryVoltage += alpha * voltage;

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
                Display::ShowForm (Display::BatteryWarning);
              }

            /* Low voltage cutoff  */
            if (BatteryVoltage < BatteryEmptyVoltage)
              {
                ::Eyebot.SetTracoState (false);
                ::Eyebot.SetLed (Led1, true);
                ::Eyebot.SetLed (Led2, false);
                ::Eyebot.SetLed (Led3, false);
                vTaskSuspendAll ();
              }

            vTaskDelay (1000);
          }
      }

    void
    InitBatteryChecker ()
      {
        if (xTaskCreate (BatteryCheckTask, NULL, 256, NULL, 2, NULL) != pdPASS)
          {
            Serial.println (F ("ERROR: TaskCreate: BatteryCheckTask"));
            while (1);
          }
      }
  }
