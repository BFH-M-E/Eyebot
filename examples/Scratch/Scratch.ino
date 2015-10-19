#include <FreeRTOS_AVR.h>
#include "Eyebot.h"

void
setup ()
  {
    Eyebot.Init ();
    Serial.begin (9600);
  }

void
loop ()
  {
    Serial.println (Eyebot.GetBatteryPercent ());
    delay (1000);

    // /* Enable Traco */
    // Eyebot.SetTracoState (true);
    // delay (200);
    //
    // /* Enable power switch  */
    // Eyebot.SetMotorState (true);
    //
    // /* Drive forwards  */
    // Eyebot.SetForwardSpeed (0.10f);
    // delay (1000);
    //
    // /* Coast out  */
    // Eyebot.SetMotorState (false);
    // delay (1000);
    //
    // /* Reenable power switch  */
    // Eyebot.SetMotorState (true);
    //
    // /* Drive backwards  */
    // Eyebot.SetForwardSpeed (-0.10f);
    // delay (1000);
    //
    // /* Stop the robot  */
    // Eyebot.Stop ();
    //
    // /* Tail wheel servo  */
    // Eyebot.SetTailWheelAngle (10);
    // delay (300);
    //
    // Eyebot.SetTailWheelAngle (-10);
    // delay (600);
    //
    // Eyebot.SetTailWheelAngle (0);
    // delay (300);
    //
    // /* Disable Traco to avoid noise */
    // Eyebot.SetTracoState (false);
    // delay (500);

  }
