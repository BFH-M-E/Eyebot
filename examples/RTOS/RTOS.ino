#include "FreeRTOS/FreeRTOS_AVR.h">"

void setup()
  {
    Serial.begin(9600);

    if (xTaskCreate(Thread1, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL) != pdPASS)
      {
        Serial.println (F ("Creation problem"));
        while (1);
      }

    // start scheduler
    vTaskStartScheduler ();
    Serial.println (F ("Insufficient RAM"));
    while (1);
  }

void
loop()
  { }

static void
Thread1 (void* param)
  {
    pinMode (LED_PIN, OUTPUT);

    while (1)
      {
        static bool state = false;
        digitalWrite (LED_PIN, state);
        state = !state;

        vTaskDelay (500);
      }
  }
