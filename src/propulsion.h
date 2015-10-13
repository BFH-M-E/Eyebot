#ifndef PROPULSION_H
#define PROPULSION_H

void InitPropulsion ();

void Stop ();

void EnableMotors ();
void DisableMotors ();

void SetForwardSpeed (float Speed);
void SetTailWheelAngle (int AngleInDegree);

#endif /* end of include guard: PROPULSION_H */
