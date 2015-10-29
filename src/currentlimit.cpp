#include "Arduino.h"

#include "currentlimit.h"
#include "definitions.h"

#include "FreeRTOS/FreeRTOS_AVR.h"

namespace BFH
  {
    namespace Currentlimit
      {
        namespace
          {
            /* Current limit in [A], measured per motor  */
            const float CurrentLimit = 0.7f;

            /* File scope variables to hold the measured current  */
            float CurrentLeft  = 0.0f;
            float CurrentRight = 0.0f;
          }

        void
        CurrentLimiterTask (void* param)
          {
            while (1)
              {
                /* Read current values from shunt resistors  */
                int valueLeft  = analogRead (CurrentSense2Pin);
                int valueRight = analogRead (CurrentSense1Pin);

                /* Convert to [A]  */
                float newCurrentLeft  = valueLeft  / 405.1f;
                float newCurrentRight = valueRight / 405.1f;

                /* Low pass  */
                const float alpha = 0.1;  /* -> time constant = 10 ms @ 1 kHz  */
                CurrentLeft  = (1 - alpha) * CurrentLeft
                    + alpha * newCurrentLeft;
                CurrentRight = (1 - alpha) * CurrentRight
                    + alpha * newCurrentRight;

                vTaskDelay (1);
              }
          }

        float
        GetCurrentLeft ()
          {
            return CurrentLeft;
          }

        float
        GetCurrentRight ()
          {
            return CurrentRight;
          }

        void
        Init ()
          {
            if (xTaskCreate (CurrentLimiterTask, NULL, 512, NULL, 3, NULL) != pdPASS)
              {
                Serial.println (F ("ERROR: TaskCreate: CurrentLimiterTask"));
                while (1);
              }
          }
      }
  }
