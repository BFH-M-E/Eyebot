#include "Eyebot.h"

void
setup ()
  {
    /* Initialize Eyebot  */
    xTaskCreate (task, NULL, 1024, NULL, 1, NULL);
    Eyebot.Init ();
  }

/* Do not change this line of code!  */
void task (void* param)  { while (1) loop (); }

void
loop ()
  {
    /* User code goes here  */
    static bool state = false;
    digitalWrite (46, state);
    state = !state;

    delay (500);
  }
