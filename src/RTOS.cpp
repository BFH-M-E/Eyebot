#include "FreeRTOS/FreeRTOS_AVR.h"
#include "arduino.h"
#include "definitions.h"

namespace BFH
  {
    void
    BlinkyTask (void* param)
      {
        pinMode (Led2Pin, OUTPUT);
        while (1)
          {
            static bool state = false;
            digitalWrite (Led2Pin, state);
            state = !state;

            vTaskDelay (50);
          }
      }

    void
    LoopUserTask (void* param)
      {
        /* Forward declaration  */
        void loop ();

        /* Call the arduino "loop" function, so that the user has a normal
           Arduino environment with a setup and loop function that behave
           as usual - except that the loop funciton is controlled by the
           RTOS kernel  */
        while (1)
          ::loop ();
      }

    void
    InitRtos ()
      {
        if (xTaskCreate (BlinkyTask, NULL, 256, NULL, 2, NULL) != pdPASS)
          {
            Serial.println (F ("ERROR: TaskCreate: BlinkyTask"));
            while (1);
          }

        if (xTaskCreate (LoopUserTask, NULL, 1024, NULL, 1, NULL) != pdPASS)
          {
            Serial.println (F ("ERROR: TaskCreate: (user)LoopUserTask"));
            while (1);
          }

        /* Start scheduler  */
        vTaskStartScheduler ();

        /* This code should not be reached (unless out of memory)  */
        Serial.println (F ("Insufficient RAM"));
        while (1);
      }
  }
