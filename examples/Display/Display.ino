#include "Eyebot.h"
#include "Wire.h"

#include "display.h"

void
setup ()
  {
    Serial.begin (9600);

    BFH::Display::Init ();
  }

void
loop ()
  {
    BFH::Display::Update ();

    Serial.println (BFH::Display::GetButton (0) ? "true" : "false");
  }
