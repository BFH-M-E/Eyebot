#include "FreeRTOS/FreeRTOS_AVR.h"
#include "arduino.h"
#include "Eyebot.h"

namespace BFH
  {
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

            vTaskDelay (1000);
          }
      }

    void
    InitRtos ()
      {
        if (xTaskCreate (BatteryCheckTask, NULL, 512,
            NULL, 2, NULL) != pdPASS)
          {
            Serial.println (F ("ERROR: TaskCreate: BatteryCheckTask"));
            while (1);
          }

        /* Start scheduler  */
        vTaskStartScheduler ();

        /* This code should not be reached (unless out of memory)  */
        Serial.println (F ("Insufficient RAM"));
        while (1);
      }
  }
