#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#define LEFT 0
#define RIGHT 1
#define posPin 0
#define negPin 1
#define stdVolt 100
#define turnVolt 50

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
        if (slight) {          
          // Right motor rotates forward
          analogWrite(motor[RIGHT][posPin], 0);
          analogWrite(motor[RIGHT][negPin], vLimU);
          // Left motor rotates forward but slow
          analogWrite(motor[LEFT][posPin], 0);
          analogWrite(motor[LEFT][negPin], vLimL);
        } else {
          // Right motor rotates forward
          analogWrite(motor[RIGHT][posPin], 0);
          analogWrite(motor[RIGHT][negPin], turnVolt+voltage);
          // Left motor rotates backward
          analogWrite(motor[LEFT][posPin], turnVolt+voltage);
          analogWrite(motor[LEFT][negPin], 0);
        }
        break;
      case 'r':
        if (slight) {
          // Left motor rotates forward
          analogWrite(motor[LEFT][posPin], 0);
          analogWrite(motor[LEFT][negPin], vLimU);
          // Right motor rotates forward but slow
          analogWrite(motor[RIGHT][posPin], 0);
          analogWrite(motor[RIGHT][negPin], vLimL);
        } else {
          // Left motor rotates forward
          analogWrite(motor[LEFT][posPin], 0);
          analogWrite(motor[LEFT][negPin], turnVolt+voltage);
          // Right motor rotates backward
          analogWrite(motor[RIGHT][posPin], turnVolt+voltage);
          analogWrite(motor[RIGHT][negPin], 0);
        }
        break;
    }
  }

  void turn90(char dir) {
    //this->move('b', turnVolt);
    //delay(150);
    this->move(dir, 0);
    // Time required to turn 90 deg at stdVolt
    delay(250);

    // Stop after turning
    this->stop();
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
