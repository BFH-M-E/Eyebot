#include "arduino.h"
#include "definitions.h"
#include "motors.h"

bool PowerSwitchEnable = true;

void
InitMotors ()
  {
    /* Configure pins as outputs  */
    pinMode (Pwm1A, OUTPUT);
    pinMode (Pwm1B, OUTPUT);
    pinMode (Pwm1EN, OUTPUT);
    pinMode (Pwm2A, OUTPUT);
    pinMode (Pwm2B, OUTPUT);
    pinMode (Pwm2EN, OUTPUT);

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
        digitalWrite (Pwm2A, reverseMode);
        digitalWrite (Pwm2B, !reverseMode);
        analogWrite (Pwm2EN, Value);
      }
    else
      {
        digitalWrite (Pwm2EN, LOW);
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
        digitalWrite (Pwm1A, !reverseMode);
        digitalWrite (Pwm1B, reverseMode);
        analogWrite (Pwm1EN, Value);
      }
    else
      {
        digitalWrite (Pwm1EN, LOW);
      }
  }
