#ifndef ENCODERS_H
#define ENCODERS_H

void InitEncoders ();

void ResetEncoders ();

float GetEncoderDistance ();

long GetEncoderTicksLeft ();
long GetEncoderTicksRight ();

#endif /* end of include guard: ENCODERS_H */
