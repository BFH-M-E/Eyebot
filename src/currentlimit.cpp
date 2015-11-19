#include "Arduino.h"

#include "battery.h"
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
            const float CurrentLimit = 1.8f;

            /* Each current measurement is compared to the CurrentLimit
               value. If a measured value exceeds the limit, a counter
               is incremented by one. If the limit is not exceeded, the
               counter is decremented by one. If the counter touches the
               ShutdownThreshold value, the system shuts down  */
            const int ShutdownThreshold = 150;

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

                /* If current limit exceeded: increment counter, otherwise
                   decrease it  */
                static int shutdownCounter = 0;
                if (CurrentLeft + CurrentRight > CurrentLimit)
                  shutdownCounter++;
                else
                  shutdownCounter--;

                /* Prevent negative values for the counter (anti wind up)  */
                if (shutdownCounter < 0)
                  shutdownCounter = 0;

                /* If counter reaches threshold (current limit exceeded for
                   a given number of times): shutdown the system  */
                else if (shutdownCounter >= ShutdownThreshold)
                  Battery::EmergencyShutdown ();

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
            if (xTaskCreate (CurrentLimiterTask, NULL, 256, NULL, 3, NULL) != pdPASS)
              {
                Serial.println (F ("ERROR: TaskCreate: CurrentLimiterTask"));
                while (1);
              }
          }
      }
  }
