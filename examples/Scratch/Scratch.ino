#include "display.h"

#include "FreeRTOS/FreeRTOS_AVR.h"

void
setup ()
  {
    Serial.begin (9600);

    pinMode (38, OUTPUT);
    digitalWrite (38, true);

    pinMode (44, OUTPUT);
    pinMode (45, OUTPUT);
    pinMode (46, OUTPUT);

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

    digitalWrite (44, false);
    digitalWrite (45, false);
    digitalWrite (46, false);

    BFH::Display::Init ();
    vTaskStartScheduler ();

    digitalWrite (44, true);
  }

  void
  BlinkyTask (void* param)
    {
      pinMode (45, OUTPUT);
      while (1)
        {
          static bool state = false;
          digitalWrite (45, state);
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
        loop ();
    }

void
loop ()
  {
    static int p = 0;
    p += 3;
    p %= 100;
    BFH::Display::ShowBatteryLevel (p);

    delay (200);
  }
