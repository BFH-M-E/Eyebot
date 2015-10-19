#include "FreeRTOS/FreeRTOS_AVR.h"
#include "arduino.h"
#include "definitions.h"
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
    BlinkyTask (void* param)
      {
        pinMode (Led2Pin, OUTPUT);
        while (1)
          {
            static bool state = false;
            digitalWrite (Led2Pin, state);
            state = !state;
            Serial.println (xTaskGetTickCount ());

            vTaskDelay (50);
          }
      }

    void
    InitRtos ()
      {
        if (xTaskCreate (BlinkyTask, NULL, 256, NULL, 2, NULL) != pdPASS)
          {
            Serial.println (F ("ERROR: TaskCreate: BlinkyTask"));
            while (1);
          }

        if (xTaskCreate (BatteryCheckTask, NULL, 256, NULL, 2, NULL) != pdPASS)
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
