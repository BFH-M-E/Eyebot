#include "arduino.h"
#include "definitions.h"
#include "encoders.h"

/* Constant to be used in the conversion from ticks to meters. This value
   determines, how far the robot "thinks" he has driven. Tweak this value by
   hand if necessary.

   e.g. if driven distance = 1.00m and robot thinks 0.95m -> tweak value down
        if driven distanec = 1.00m and robot thinks 1.05m -> tweak value up  */
const float MeterToTicksFactor = 3400.0f;


/* ----- Code begins here: Do not change anything after this line -----  */

volatile long TicksLeft = 0;
volatile long TicksRight = 0;

void IsrEncoderTick1A ();
void IsrEncoderTick1B ();
void IsrEncoderTick2A ();
void IsrEncoderTick2B ();

void
InitEncoders ()
  {
    /* Configure pins as inputs  */
    pinMode (Encoder1A, INPUT);
    pinMode (Encoder1B, INPUT);
    pinMode (Encoder2A, INPUT);
    pinMode (Encoder2B, INPUT);

    /* Configure interrupts  */
    attachInterrupt (digitalPinToInterrupt (Encoder1A), IsrEncoderTick1A,
        RISING);
    attachInterrupt (digitalPinToInterrupt (Encoder1B), IsrEncoderTick1B,
        RISING);
    attachInterrupt (digitalPinToInterrupt (Encoder2A), IsrEncoderTick2A,
        RISING);
    attachInterrupt (digitalPinToInterrupt (Encoder2B), IsrEncoderTick2B,
        RISING);
  }

void
ResetEncoders ()
  {
    /* Disable interrupts since the reset operation is non-atomic  */
    cli();

    /* Reset counters  */
    TicksLeft = 0L;
    TicksRight = 0L;

    /* Reenable interrupts  */
    sei();
  }

long
GetEncoderTicksLeft ()
  {
    return TicksLeft;
  }

long
GetEncoderTicksRight ()
  {
    return TicksRight;
  }

float
GetDrivenDistance ()
  {
    long ticksLeft  = GetEncoderTicksLeft ();
    long ticksRight = GetEncoderTicksRight ();

    /* Calculate average of both encoder values. This value is approximately
       equal to the mean driven distance of the robot  */
    long ticksAverage = (ticksLeft + ticksRight) / 2;

    /* Convert from ticks to meters for better human readability  */
    return float (ticksAverage) / MeterToTicksFactor;
  }

void
IsrEncoderTick1A ()
  {
    /* Operations can be treated as atomic since interrupt nesting is disabled
       by default  */

    if (digitalRead (Encoder1B))
      TicksRight++;
    else
      TicksRight--;
  }

void
IsrEncoderTick1B ()
  {
    /* Operations can be treated as atomic since interrupt nesting is disabled
       by default  */

    if (digitalRead (Encoder1A))
      TicksRight--;
    else
      TicksRight++;
  }

void
IsrEncoderTick2A ()
  {
    /* Operations can be treated as atomic since interrupt nesting is disabled
       by default  */

    if (digitalRead (Encoder2B))
      TicksLeft--;
    else
      TicksLeft++;
  }

void
IsrEncoderTick2B ()
  {
    /* Operations can be treated as atomic since interrupt nesting is disabled
       by default  */

    if (digitalRead (Encoder2A))
      TicksLeft++;
    else
      TicksLeft--;
  }
