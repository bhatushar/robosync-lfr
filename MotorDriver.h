#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#define LEFT 0
#define RIGHT 1
#define posPin 0
#define negPin 1
#define stdVolt 150

class MotorDriver {
private:
  int motor[2][2];

public:
  MotorDriver(int out[]) {
    // Constructor
    // Initializing motor motor as OUTPUT
    for(int i = 0, k = 0; i < 2; i++)
      for(int j = 0; j < 2; j++, k++) {
        motor[i][j] = out[k];
        pinMode(motor[i][j], OUTPUT);
      }
  }

  void move(char direction, int voltage, bool slight = false){
    /*
    Function to move the bot in desired direction at given voltage
    */
    int vLimU = (stdVolt+voltage >= 255) ? 255 : stdVolt+voltage;
    int vLimL = (stdVolt-voltage <= 0) ? 0 : stdVolt-voltage;
    switch(direction) {
      case 'b':
        // Left motor rotates clockwise
        analogWrite(motor[LEFT][posPin], voltage);
        analogWrite(motor[LEFT][negPin], 0);
        // Right motor rotates clockwise
        analogWrite(motor[RIGHT][posPin], voltage);
        analogWrite(motor[RIGHT][negPin], 0);
        break;
      case 'f':
        // Left motor rotates anti-clockwise
        analogWrite(motor[LEFT][posPin], 0);
        analogWrite(motor[LEFT][negPin], voltage);
        // Right motor rotates anti-clockwise
        analogWrite(motor[RIGHT][posPin], 0);
        analogWrite(motor[RIGHT][negPin], voltage);
        break;
      case 'l':
        // Right motor rotates forward
        analogWrite(motor[RIGHT][posPin], 0);
        analogWrite(motor[RIGHT][negPin], vLimU);

        if (slight) {          
          // Left motor rotates forward but slow
          analogWrite(motor[LEFT][posPin], 0);
          analogWrite(motor[LEFT][negPin], vLimL);
        } else {
          // Left motor rotates backward
          analogWrite(motor[LEFT][posPin], vLimU);
          analogWrite(motor[LEFT][negPin], 0);
        }
        break;
      case 'r':        
        // Left motor rotates forward
        analogWrite(motor[LEFT][posPin], 0);
        analogWrite(motor[LEFT][negPin], vLimU);

        if (slight) {          
          // Right motor rotates forward but slow
          analogWrite(motor[RIGHT][posPin], 0);
          analogWrite(motor[RIGHT][negPin], vLimL);
        } else {
          // Right motor rotates backward
          analogWrite(motor[RIGHT][posPin], vLimU);
          analogWrite(motor[RIGHT][negPin], 0);
        }
        break;
    }
  }

  void stop() {
    for(int i = 0; i < 2; i++)
      for(int j = 0; j < 2; j++)
        digitalWrite(motor[i][j], LOW);
  }

};

#undef LEFT
#undef RIGHT
#undef posPin
#undef negPin

#endif
