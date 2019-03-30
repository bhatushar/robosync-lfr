#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#define LEFT 0
#define RIGHT 1
#define posPin 0
#define negPin 1
#define stdVolt 50

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

  void move(char direction, int voltage){
    /*
    Function to move the bot in desired direction at given voltage
    */
    switch(direction) {
      case 'f':
        // Left motor rotates clockwise
        analogWrite(motor[LEFT][posPin], voltage);
        analogWrite(motor[LEFT][negPin], 0);
        // Right motor rotates clockwise
        analogWrite(motor[RIGHT][posPin], voltage);
        analogWrite(motor[RIGHT][negPin], 0);
        break;
      case 'b':
        // Left motor rotates anti-clockwise
        analogWrite(motor[LEFT][posPin], 0);
        analogWrite(motor[LEFT][negPin], voltage);
        // Right motor rotates anti-clockwise
        analogWrite(motor[RIGHT][posPin], 0);
        analogWrite(motor[RIGHT][negPin], voltage);
        break;
      case 'r':
        // Left motor rotates clockwise
        analogWrite(motor[LEFT][posPin], stdVolt+voltage);
        analogWrite(motor[LEFT][negPin], 0);
        // Right motor rotates anti-clockwise
        analogWrite(motor[RIGHT][posPin], 0);
        analogWrite(motor[RIGHT][negPin], stdVolt+voltage);
        
        break;
      case 'l':
        // Left motor rotates anti-clockwise
        analogWrite(motor[LEFT][posPin], 0);
        analogWrite(motor[LEFT][negPin], stdVolt+voltage);
        // Right motor rotates clockwise
        analogWrite(motor[RIGHT][posPin], stdVolt+voltage);
        analogWrite(motor[RIGHT][negPin], 0);
        
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
