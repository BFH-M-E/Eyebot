#ifndef MOTORS_H
#define MOTORS_H

void InitMotors ();

void EnablePowerSwitch ();
void DisablePowerSwitch ();

void SetPwmLeft (int Value);
void SetPwmRight (int Value);

#endif /* end of include guard: MOTORS_H */
