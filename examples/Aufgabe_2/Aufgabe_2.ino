#include "Eyebot.h"
#include "Wire.h"

#include "encoders.h"

void setup ()
{
  Serial.begin(9600);
  Eyebot.Init (RobotColor::Red);
}

void loop ()  {
  //Drive strait 0.5m
  DriveStraitDistance(0.1, 0.5);
  delay(200);
  // Turn 90 degrees
  DriveRightAngle(0.1, -40);
  delay(20);
}

void DriveStraitDistance(float speed, float distance) {

  Eyebot.Stop();
  Eyebot.SetTailWheelAngle(0);
  float DrivenDistance = GetDrivenDistance();
  Eyebot.SetForwardSpeed (speed);
  // forward
  if (speed > 0) {
    while (GetDrivenDistance() < DrivenDistance  + distance) {
      Serial.print("Distanz Soll:   ");
      Serial.print(DrivenDistance + distance);
      Serial.print("   Distanz Ist:  ");
      Serial.println(GetDrivenDistance());
    }
  }
  //reverse
  else {
    while (GetDrivenDistance() > DrivenDistance  - distance) {
      Serial.print("Distanz Soll:   ");
      Serial.print(DrivenDistance - distance);
      Serial.print("   Distanz Ist:  ");
      Serial.println(GetDrivenDistance());
    }
  }
  Eyebot.Stop();
}


void DriveRightAngle(float speed, int angle) {

  Eyebot.Stop();
  Eyebot.SetTailWheelAngle(angle);
  delay(20);

  int LeftTicks = GetEncoderTicksLeft();
  int RightTicks = GetEncoderTicksRight();
  int OldDeltaS = abs(LeftTicks - RightTicks);
  int DeltaS = 0;

  Eyebot.SetForwardSpeed(speed);
  do {
    LeftTicks = GetEncoderTicksLeft();
    RightTicks = GetEncoderTicksRight();
    DeltaS = abs(LeftTicks - RightTicks);
    // Wert Berechnet 908, Wert Empirisch 765,
    Serial.print("DeltaS Soll:   ");
    Serial.print(OldDeltaS + 765);
    Serial.print("   DeltaS Ist:  ");
    Serial.println(DeltaS);
  } while (DeltaS < OldDeltaS + 765);
  Eyebot.Stop();
}
