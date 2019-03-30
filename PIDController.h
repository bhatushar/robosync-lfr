#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

float P, I, D;

int PID(int err, int lastErr) {
  // TODO adjust kP
  float kP = 0.5, 
    kI = 0, 
    kD = 0;
  P = kP * err;
  I += err;
  D = kD * (err - lastErr);
  return abs(P + (kI * I) + D);
}

#undef kP
#undef kI
#undef kD

#endif
