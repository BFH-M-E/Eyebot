#include "arduino.h"
#include "definitions.h"
#include "encoders.h"

using namespace BFH;

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
    pinMode (Encoder1APin, INPUT);
    pinMode (Encoder1BPin, INPUT);
    pinMode (Encoder2APin, INPUT);
    pinMode (Encoder2BPin, INPUT);

    /* Configure interrupts  */
    attachInterrupt (digitalPinToInterrupt (Encoder1APin), IsrEncoderTick1A,
        RISING);
    attachInterrupt (digitalPinToInterrupt (Encoder1BPin), IsrEncoderTick1B,
        RISING);
    attachInterrupt (digitalPinToInterrupt (Encoder2APin), IsrEncoderTick2A,
        RISING);
    attachInterrupt (digitalPinToInterrupt (Encoder2BPin), IsrEncoderTick2B,
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

    if (digitalRead (Encoder1BPin))
      TicksRight++;
    else
      TicksRight--;
  }

void
IsrEncoderTick1B ()
  {
    /* Operations can be treated as atomic since interrupt nesting is disabled
       by default  */

    if (digitalRead (Encoder1APin))
      TicksRight--;
    else
      TicksRight++;
  }

void
IsrEncoderTick2A ()
  {
    /* Operations can be treated as atomic since interrupt nesting is disabled
       by default  */

    if (digitalRead (Encoder2BPin))
      TicksLeft--;
    else
      TicksLeft++;
  }

void
IsrEncoderTick2B ()
  {
    /* Operations can be treated as atomic since interrupt nesting is disabled
       by default  */

    if (digitalRead (Encoder2APin))
      TicksLeft++;
    else
      TicksLeft--;
  }
