#include "Eyebot.h"

void
setup ()
  {
    /* Initialize Eyebot library  */
    xTaskCreate (task, NULL, 512, NULL, 2, NULL);

    Serial.begin (9600);

    vTaskStartScheduler ();


    Eyebot.Init ();
  }

void
task (void* param)
  {
    pinMode (44, OUTPUT);
    while (1)
      {
        static bool state = false;
        digitalWrite (44, state);
        state = !state;
        Serial.println (xTaskGetTickCount ());


        vTaskDelay (50);
      }
  }

void
loop ()
  { }
