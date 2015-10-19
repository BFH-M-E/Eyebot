#include "FreeRTOS/FreeRTOS_AVR.h"
#include "arduino.h"

namespace BFH
  {
    void
    InitRtos ()
      {
        /*
        if (xTaskCreate (Thread1, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL) != pdPASS)
          {
            Serial.println (F ("Creation problem"));
            while (1);
          } */

        /* Start scheduler  */
        vTaskStartScheduler ();

        /* This code should not be reached (unless out of memory)  */
        Serial.println (F ("Insufficient RAM"));
        while (1);
      }
  }
