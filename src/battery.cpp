#include "arduino.h"
#include "definitions.h"
#include "battery.h"

/* Conversion factor to trim the voltage divider (there should be no need
   to change this value, as long as 1 % resistors are used, as they produce a
   total error of less than 1.5 %)  */
const float VoltageDividerFactor = 0.3125f;



/* ----- Code begins here: Do not change anything after this line -----  */

float GetBatteryVoltage ()
  {
    /* Read battery voltage value  */
    int batteryValue = analogRead (Battery);

    /* The voltage reference is made by the Arduino MEGA board's 5 V voltage
       regulator. Therefore, we can assume 5.0 V as reference  */
    float analogVoltage = batteryValue * 5.0f / 1023.0f;

    /* Compensate influence of voltage divider  */
    float batteryVoltage = analogVoltage / VoltageDividerFactor;

    return batteryVoltage;
  }
