#include "arduino.h"
#include "definitions.h"
#include "motors.h"

using namespace BFH;

bool PowerSwitchEnable = true;

void
InitMotors ()
  {
    /* Configure pins as outputs  */
    pinMode (Pwm1APin, OUTPUT);
    pinMode (Pwm1BPin, OUTPUT);
    pinMode (Pwm1ENPin, OUTPUT);
    pinMode (Pwm2APin, OUTPUT);
    pinMode (Pwm2BPin, OUTPUT);
    pinMode (Pwm2ENPin, OUTPUT);

    /* Set timer3 divisor to 1, for PWM frequency of 31372.55 Hz  */
    TCCR3B = TCCR3B & 0b11111000 | 0x01;
    /* Set timer4 divisor to 1, for PWM frequency of 31372.55 Hz  */
    TCCR4B = TCCR4B & 0b11111000 | 0x01;
  }

void
EnablePowerSwitch ()
  {
    PowerSwitchEnable = true;
  }

void
DisablePowerSwitch ()
  {
    PowerSwitchEnable = false;
  }

void
SetPwmLeft (int Value)
  {
    /* Limit parameter value  */
    if (Value > 255)  Value = 255;
    else if (Value < -255) Value = -255;

    /* Handle negative values  */
    bool reverseMode = false;
    if (Value < 0)
      {
        Value = -Value;
        reverseMode = true;
      }

    if (PowerSwitchEnable)
      {
        /* Control motor  */
        digitalWrite (Pwm2APin, reverseMode);
        digitalWrite (Pwm2BPin, !reverseMode);
        analogWrite (Pwm2ENPin, Value);
      }
    else
      {
        digitalWrite (Pwm2ENPin, LOW);
      }
  }

void
SetPwmRight (int Value)
  {
    /* Limit parameter value  */
    if (Value > 255)  Value = 255;
    else if (Value < -255) Value = -255;

    /* Handle negative values  */
    bool reverseMode = false;
    if (Value < 0)
      {
        Value = -Value;
        reverseMode = true;
      }

    if (PowerSwitchEnable)
      {
        /* Control motor  */
        digitalWrite (Pwm1APin, !reverseMode);
        digitalWrite (Pwm1BPin, reverseMode);
        analogWrite (Pwm1ENPin, Value);
      }
    else
      {
        digitalWrite (Pwm1ENPin, LOW);
      }
  }
