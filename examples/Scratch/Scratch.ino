#include "battery.h"
#include "definitions.h"
#include "encoders.h"
#include "motors.h"
#include "propulsion.h"
#include "Servo.h"

void
setup ()
{
  /* Enable 5 V power supply  */
  pinMode (TracoEnable, OUTPUT);
  digitalWrite (TracoEnable, HIGH);

  /* Initialize hardware drivers  */
  InitPropulsion ();

  Serial.begin (9600);

  pinMode (Button1, INPUT);
  pinMode (Button2, INPUT);
  pinMode (Button3, INPUT);
}

void
loop ()
{
  if (GetBatteryVoltage () < 11.0f)
    {
      digitalWrite (TracoEnable, LOW);
      delay (1000);
    }
  else
    {
      digitalWrite (TracoEnable, HIGH);
    }

  SetForwardSpeed (0.05f);

  if (digitalRead (Button1))
    EnableMotors ();
  if (digitalRead (Button2))
    DisableMotors ();

  SetTailWheelAngle (0);

  delay (100);
}
