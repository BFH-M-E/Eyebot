#include "arduino.h"
#include "definitions.h"
#include "encoders.h"
#include "Eyebot.h"
#include "motors.h"
#include "propulsion.h"
#include "Servo.h"

#include "FreeRTOS/FreeRTOS_AVR.h"

using namespace BFH;

/* P and I value for the PI controller. The values do not correspond to
   something human readable, just tweak them as needed by hand  */
const int PValue = 300;
const int IValue = 200;

/* Ramp steepness: the higher this value, the faster the robot accelerates to
   after an input value change  */
const int RampStep = 2;

/* Conversion factor from m/s to steps/tick. Tweak manually if the parameter
   of the SetSpeedLeft/Right functions seems to be inacurate

   e.g. SetSpeedLeft (1.0f) leads to 1.1 m/s -> tweak conversion factor down
        SetSpeedLeft (1.0f) leads to 0.9 m/s -> tweak conversion factor up  */
const int SpeedConversionFactor = 100;

/* Offset to be applied to the rear wheel servo  */
const int TailWheelAngleOffset = 74;



/* ----- Code begins here: Do not change anything after this line -----  */

/* This factor is used to allow finer adjustments of P and I controller
   parameter. Leave it as it is  */
const int CompressionFactor = 100;

/* Minimum and maximum speed for the robot  */
const float MinSpeed = 0.03f;
const float MaxSpeed = 0.80f;

const float pi = 3.1415f;

int integratedErrorLeft = 0;
int integratedErrorRight = 0;

int TargetSpeedLeft  = 0;
int TargetSpeedRight = 0;

float TargetSpeed = 0.0f;
int TailServoAngle = 0;

Servo TailWheelServo;

void ControlMotorTask (void* param)
  {
    /* Initialize last wake time with current time  */
    TickType_t lastWakeTime = xTaskGetTickCount();

    while (1)
      {
        /* Read encoder values  */
        long encoderValueLeft  = GetEncoderTicksLeft ();
        long encoderValueRight = GetEncoderTicksRight ();

        static long lastEncoderValueLeft  = 0;
        static long lastEncoderValueRight = 0;

        /* Velocity is way per time. We normalize the time to 1, as the ISR is
           called periodically and we have no strict need for human readable
           values  */
        int speedLeft  = (encoderValueLeft  - lastEncoderValueLeft)  / 1;
        int speedRight = (encoderValueRight - lastEncoderValueRight) / 1;

        /* Backup encoder value  */
        lastEncoderValueLeft  = encoderValueLeft;
        lastEncoderValueRight = encoderValueRight;

        static int limitedTargetSpeedLeft = 0;
        static int limitedTargetSpeedRight = 0;

        /* Limit acceleration to prevent wheelspin  */
        if (TargetSpeedLeft > limitedTargetSpeedLeft + RampStep)
          limitedTargetSpeedLeft += RampStep;
        else if (TargetSpeedLeft < limitedTargetSpeedLeft - RampStep)
          limitedTargetSpeedLeft -= RampStep;
        else
          limitedTargetSpeedLeft = TargetSpeedLeft;

        if (TargetSpeedRight > limitedTargetSpeedRight + RampStep)
          limitedTargetSpeedRight += RampStep;
        else if (TargetSpeedRight < limitedTargetSpeedRight - RampStep)
          limitedTargetSpeedRight -= RampStep;
        else
          limitedTargetSpeedRight = TargetSpeedRight;

        /* Calculate speed error  */
        int speedErrorLeft = limitedTargetSpeedLeft - speedLeft;
        int speedErrorRight = limitedTargetSpeedRight - speedRight;

        /* Calculate integrated speed error  */
        integratedErrorLeft += speedErrorLeft;
        integratedErrorRight += speedErrorRight;

        /* Prevent integral wind up  */
        if (integratedErrorLeft  > 200)  integratedErrorLeft  = 200;
        else if (integratedErrorLeft  < -200) integratedErrorLeft  = -200;
        if (integratedErrorRight > 200)  integratedErrorRight = 200;
        else if (integratedErrorRight < -200) integratedErrorRight = -200;

        /* PID controller  */
        long outputLeft = PValue * speedErrorLeft
            + IValue * integratedErrorLeft;
        long outputRight = PValue * speedErrorRight
            + IValue * integratedErrorRight;

        /* Control motors  */
        SetPwmLeft (outputLeft / CompressionFactor);
        SetPwmRight (outputRight / CompressionFactor);

        vTaskDelayUntil (&lastWakeTime, 20);
      }
  }

void
InitPropulsion ()
  {
    /* Initialize hardware  */
    InitEncoders ();
    InitMotors ();

    /* Initialize task to control motors with high priority  */
    if (xTaskCreate (ControlMotorTask, NULL, 512, NULL, 3, NULL) != pdPASS)
      {
        Serial.println (F ("ERROR: TaskCreate: ControlMotorTask"));
        while (1);
      }

    TailWheelServo.attach (TailWheelServoPin);
    SetTailWheelAngle (0);
  }

void
SetSpeedLeft (float Speed)
  {
    /* Convert parameter from m/s to a more controller friendly format  */
    TargetSpeedLeft = int (Speed * SpeedConversionFactor);
  }

void
SetSpeedRight (float Speed)
  {
    /* Convert parameter from m/s to a more controller friendly format  */
    TargetSpeedRight = int (Speed * SpeedConversionFactor);
  }

void
Stop ()
  {
    /* Set speed to zero (the acceleration ramp is applied automatically)  */
    SetForwardSpeed (0.0f);
  }

void
ResetIntegratedError ()
  {
    /* Prevent interrupts  */
    cli();

    /* Reset integrated error  */
    integratedErrorLeft = 0;
    integratedErrorRight = 0;

    /* Resume interrupts  */
    sei();
  }

void
EnableMotors ()
  {
    ResetIntegratedError ();

    SetForwardSpeed (0.0f);
    EnablePowerSwitch ();
  }

void
DisableMotors ()
  {
    DisablePowerSwitch ();
  }

void
SetForwardSpeed (float Speed)
  {
    if (Speed < 0.0f)
      {
        /* Limit speed to reasonable amounts  */
        if (Speed > -MinSpeed)  Speed = 0.0f;
        if (Speed < -MaxSpeed)  Speed = -MaxSpeed;
      }
    else
      {
        /* Limit speed to reasonable amounts  */
        if (Speed < MinSpeed)  Speed = 0.0f;
        if (Speed > MaxSpeed)  Speed = MaxSpeed;
      }

    /* Backup target speed, so that other functions know, how fast the robot
       was told to move. This is needed to be able to send new SetForwardSpeed
       commands with the same speed. E.g. after the rear wheel has turned, the
       SetForwardSpeed function can be used to update the electric differential
       system  */
    TargetSpeed = Speed;

    if (TailServoAngle < 2 && TailServoAngle > -2)
      {
        /* Tailwheel has almost no displacement, so we can drive straight  */

        SetSpeedLeft (Speed);
        SetSpeedRight (Speed);
      }
    else
      {
        /* Tailwheel has a displacement, so that the two motors need different
           angular velocities  */

        /* Calculate position of the rotation point (arround which the robot
           drives). The origin of the used coordinate system is in the middle
           of the main wheels  */
        int alfa = 90 - TailServoAngle;
        float turnPointX = 0;
        float turnPointY = tan (alfa / 180.0f * pi) * 0.18f;

        /* Apply theorem of intersecting lines to calculate the target speed for
           each of the two main wheels  */
        float speedLeft  = Speed * (turnPointY + 0.085f) / turnPointY;
        float speedRight = Speed * (turnPointY - 0.085f) / turnPointY;

        SetSpeedLeft (speedLeft);
        SetSpeedRight (speedRight);
      }
  }

void
SetTailWheelAngle (int AngleInDegree)
  {
    /* Limit parameter to legal range  */
    if (AngleInDegree > 40)  AngleInDegree = 40;
    if (AngleInDegree < -40) AngleInDegree = -40;

    /* Save angle for later use in the electrical differential  */
    TailServoAngle = AngleInDegree;

    int totalAngle = AngleInDegree + TailWheelAngleOffset;

    /* Limit angle to legal range to prevent servo damage  */
    if (totalAngle > 150) totalAngle = 150;
    if (totalAngle < 40)  totalAngle = 40;

    TailWheelServo.write (totalAngle);

    /* Send a new drive command so that the individual speed for both motors
       is calculated again (electronic differential)  */
    SetForwardSpeed (TargetSpeed);
  }
