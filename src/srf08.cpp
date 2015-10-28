#include "arduino.h"
#include "srf08.h"
#include "inline/Wire/Wire.h"

#include "FreeRTOS/FreeRTOS_AVR.h"

namespace BFH
  {
    /* Srf08 nullptr array  */
    Srf08* srf[MaxNumberOfSrfs] = {};

    SrfData srfData[MaxNumberOfSrfs];

    SrfData::SrfData ()
        : SrfData (0)
      { }

    SrfData::SrfData (int Range)
        : SrfData (Range, millis ())
      { }

    SrfData::SrfData (int Range, long Timestamp)
        : _Range (Range), _Timestamp (Timestamp)
      { }

    int
    SrfData::GetData ()
      {
        return _Range;
      }

    long
    SrfData::GetTimestamp ()
      {
        return _Timestamp;
      }

    Srf08::Srf08 (byte Address)
        : _Address (Address >> 1)
      {
        /* Initialize Srf08  */
        Wire.beginTransmission (_Address);
        Wire.write (0x02);	/* RANGE register  */
        Wire.write (0x2E);	/* Set range to approx. 2 m (see datasheet)  */
        Wire.endTransmission ();
      }

    void
    Srf08::StartMeasurement ()
      {
        /* Begin measurement, data are available approximately 70 ms later  */
        Wire.beginTransmission (_Address);
        Wire.write (0x00);  /* COMMAND register  */
        Wire.write (0x51);  /* Start ranging (see SRF08 datasheet)  */
        Wire.endTransmission ();
      }

    SrfData
    Srf08::GetData ()
      {
        /* Receive data from srf  */
        int distance = 0;
        Wire.beginTransmission (_Address);
        Wire.write (0x02);  /* RANGE register  */
        Wire.endTransmission ();
        Wire.requestFrom (_Address, static_cast<byte> (2));

        /* If too few data is available, return -1 as error code */
        if (Wire.available () >= 2)
          {
            /* Cast to int for << to be valid  */
            distance = static_cast<int> (Wire.read ()) << 8;
            distance |= static_cast<int> (Wire.read ());

            /* Limit range of valid data  */
            if (distance < 5)    distance = 5;
            if (distance > 100)  distance = 100;
          }
        else
          {
            /* Mark measurement as invalid  */
            distance = -1;
          }

        Wire.endTransmission ();

        /* Return SrfData object (with data -1 if something went wrong)  */
        SrfData data (distance);
        return data;
      }

    void
    Srf08Task (void* param)
      {
        while (1)
          {
            for (int i = 0; i < MaxNumberOfSrfs; ++i)
              {
                /* If current srf slot is empty: continue  */
                if (!srf[i])
                  continue;

                /* Start measurement  */
                srf[i]->StartMeasurement ();

                /* Wait for the srf to measure  */
                vTaskDelay (70);

                /* Receive srf data  */
                srfData[i] = srf[i]->GetData ();
              }
          }
      }

    void
    InitSrf ()
      {
        srf[0] = new Srf08 (0xE0);
        srf[1] = new Srf08 (0xE2);
        srf[2] = new Srf08 (0xE4);
        srf[3] = new Srf08 (0xE6);

        if (xTaskCreate (Srf08Task, NULL, 256, NULL, 2, NULL) != pdPASS)
          {
            Serial.println (F ("ERROR: TaskCreate: Srf08Task"));
            while (1);
          }
      }

    SrfData
    GetSrfData (int Name)
      {
        if (Name < 0 || Name > MaxNumberOfSrfs)
          return SrfData ();

        return srfData[Name];
      }
  }
