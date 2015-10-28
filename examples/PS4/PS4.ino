#include "Eyebot.h"
#include "Wire.h"

#include <SPI.h>
/* USB Host Lib */
#include <PS4BT.h>
#include <usbhub.h>

//#define PAIRINGMODE

USB Usb;
/* create Bluetooth Dongle instance */
BTD Btd(&Usb);

#ifdef PAIRINGMODE
PS4BT PS4(&Btd, PAIR);      // Pairing Mode
#else
PS4BT PS4(&Btd);            // Normal Mode
#endif

void
setup ()
  {
    Serial.begin(9600);
    Eyebot.Init (RobotColor::Red);

    if (Usb.Init() == -1) {
        Serial.println("USB Init NOT OK");     //USB init not OK
    } else {
        Serial.println("USB Init OK");          //USB init OK
    }

  }

void
loop ()
  {
    //vTaskSuspendAll ();
    //Usb.Task();
    //xTaskResumeAll ();
    delay(200);
    Serial.print("alive");
  }
