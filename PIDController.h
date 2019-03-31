#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

float P, I, D;
int lastErr = 0; // Variable to store deviation calculated in previous cycle

int PID(int dev) {
  // TODO adjust kP
  float kP, kI, kD;
  int err = abs(dev - 35);
  if (25 < dev && dev < 45) {
    // Constants for low degree error
    kP = 1.5; kI = 0; kD = 0;
  } else {
    // Constants for high degree error
    kP = 1; kI = 0; kD = 0;
  }
  //kP = 7; kI = 0; kD = 0;
  P = kP * err;
  I += err;
  D = kD * (err - lastErr);
  lastErr = err;
  return abs(P + (kI * I) + D);
}

#undef kP
#undef kI
#undef kD

#endif
