#include "arduino.h"
#include "Eyebot.h"
#include "srf08.h"
#include "Wire.h"

#include "FreeRTOS/FreeRTOS_AVR.h"

namespace BFH
  {
    /* Initialize array of nullptr  */
    Srf08* srf[4] = {};

    Srf08::Srf08 (byte Address)
        : I2cAddress (Address >> 1)
      {

vTaskSuspendAll ();
        Wire.beginTransmission (I2cAddress);
        Wire.write (0x02);	/* RANGE register  */
        Wire.write (0x2E);	/* Set range to approx. 2 m (see SRF08 datasheet)  */
        Wire.endTransmission ();
xTaskResumeAll ();
      }

    int
    Srf08::GetDistance ()
      {
        int distance = Distance;

        /* Filter values that are not plausible  */
        if (distance < 3) distance = 0;
        if (distance > 60) distance = 0;

        return distance;
      }

    void
    Srf08Task (void* param)
      {
        srf[0] = new Srf08 (0xE0);
        srf[1] = new Srf08 (0xE2);
        // if (::Eyebot.Color == RobotColor::Blue)
        //   {
        //     srf[2] = new Srf08 (0xE4);
        //     srf[3] = new Srf08 (0xE6);
        //   }

        while (1)
          {
            for (int i = 0; i < 4; ++i)
              {
Serial.println (i);

                /* If there is no srf at a given address: skip this srf  */
                if (!srf[i])
                  continue;

Serial.println (i);

                Wire.beginTransmission (srf[i]->I2cAddress);
                Wire.write (0x00);  /* COMMAND register  */
                Wire.write (0x51);  /* Start ranging (see SRF08 datasheet)  */
                Wire.endTransmission ();

                delay (70);  /* Wait until ranging is done  */

                int distance = 0;
                Wire.beginTransmission (srf[i]->I2cAddress);
                Wire.write (0x02);  /* RANGE register  */
                Wire.endTransmission ();
                Wire.requestFrom (srf[i]->I2cAddress, static_cast<byte> (2));

                /* If not enough data available (for any reason): skip srf  */
                if (Wire.available () < 2)
                  continue;

                distance = Wire.read () << 8;
                distance |= Wire.read ();
                Wire.endTransmission ();

                srf[i]->Distance = distance;

Serial.println (srf[i]->GetDistance ());
              }
          }
      }

    void
    InitSrf ()
      {
        if (xTaskCreate (Srf08Task, NULL, 256, NULL, 2, NULL) != pdPASS)
          {
            Serial.println (F ("ERROR: TaskCreate: Srf08Task"));
            while (1);
          }
      }

    int
    GetSrfDistance (int Srf)
      {
        /* Enter critical section (keep short, as it compromises the odometry
           measurement)  */
        noInterrupts();

        int distance = 0;
        if (srf[Srf])
          distance = srf[Srf]->GetDistance ();

        /* Leave critical section  */
        interrupts ();

        return distance;
      }
  }
