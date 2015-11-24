#include "arduino.h"
#include "inline/USB/PS4BT.h"

#ifdef ARDUINO_AVR_ADK
  #include "SPI.h"
#endif

#include "FreeRTOS/FreeRTOS_AVR.h"

//#define PAIRINGMODE

const int initValue = 127;

namespace BFH {
    namespace PS4 {
        namespace {
            USB Usb;
            /* create Bluetooth Dongle instance */
            BTD Btd(&Usb);

            #ifdef PAIRINGMODE
              PS4BT PS4(&Btd, PAIR);      // Pairing Mode
            #else
              PS4BT PS4(&Btd);            // Normal Mode
            #endif
          }

    int GetJoystickLeftX() {
      if (PS4.connected()) {
        return PS4.getAnalogHat(LeftHatX);
      }
      return  initValue;
    }

    int GetJoystickLeftY() {
      if (PS4.connected()) {
        return PS4.getAnalogHat(LeftHatY);
      }
      return initValue;
    }

    int GetJoystickRightX() {
      if (PS4.connected()) {
        return PS4.getAnalogHat(RightHatX);
      }
      return initValue;
    }

    int GetJoystickRightY() {

      if (PS4.connected()) {
        return PS4.getAnalogHat(RightHatY);
      }
      return initValue;
    }

    void PS4Task(void* param) {
      while (1) {
        Usb.Task();
        vTaskDelay(5);
      }
    }

    void Init() {
        if (Usb.Init() == -1) {
              Serial.println("USB Init NOT OK");     //USB init not OK
        } else {
              Serial.println("USB Init OK");          //USB init OK
        }

        if (xTaskCreate (PS4Task, NULL, 1024, NULL, 2, NULL) != pdPASS) {
            Serial.println (F ("ERROR: TaskCreate: PS4Task"));
            while (1);
        }
      }
    }
  }
