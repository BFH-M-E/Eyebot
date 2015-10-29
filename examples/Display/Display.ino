#include "Eyebot.h"

void
setup ()
  {
    Serial.begin(9600);
    Eyebot.Init (RobotColor::Red);
    Eyebot.SetLineSensorState(1);
}
void
loop ()
  {
  Serial.print(Eyebot.GetLineSensor (1));
  Serial.print("  ");
  Serial.print(Eyebot.GetLineSensor (2));
  Serial.print("  ");
  Serial.print(Eyebot.GetLineSensor (3));
  Serial.print("  ");
  Serial.println(Eyebot.GetLineSensor (4));

}
