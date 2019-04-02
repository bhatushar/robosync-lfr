#ifndef LINEDETECTOR_H
#define LINEDETECTOR_H

#define MAX_SENSOR 8

struct IRSensor {
  int pin,      // The pin to which the sensor is connected
      weight;   // The weight assigned to each pin
  bool val;
};

class LineDetector {
private:
  IRSensor sensor[MAX_SENSOR];
  int analogPin;
  int zeroSensor, onSensor;

public:
  LineDetector(int pins[], int analog) {
    zeroSensor = 0;

    // Assigning pins to each sensor
    for(int i = 0; i < MAX_SENSOR; i++) {
      sensor[i].pin = pins[i];
      pinMode(sensor[i].pin, INPUT);
    }

    // Assign analog pin
    analogPin = analog;
    pinMode(analogPin, INPUT);

    // Assigning weight to each sensor
    int even = !(MAX_SENSOR % 2); // Checking if total sensors are even or odd
    int value = even ? -(MAX_SENSOR/2 - 1) : -(MAX_SENSOR/2) ; //Weight which is to be assigned
    for(int i = 0; i < MAX_SENSOR; i++, value++) {
      if(even && i == MAX_SENSOR/2)
        // Additional condition for even sensors
        // Two sensors in middle should have weight = 0
        value--;
      sensor[i].weight = value; //Adding weight to each sensor
    }
  }

  int calcDeviation() {
    // Read data from digital pins for future use
    for (int i = 0; i < MAX_SENSOR; i++)
      sensor[i].val = digitalRead(sensor[i].pin);

    // Find line position
    int readVal = analogRead(analogPin);
    int positionVal = ((float)readVal/921)*70;
    return positionVal;
  }

  bool isCrossSection() {
    for (int i = 0; i < MAX_SENSOR; i++)
      if (sensor[i].val == LOW)
        return false;
    return true;
  }

  bool is90Turn(char side) {
    bool status = true;
    switch(side) {
      case 'l':
        for (int i = 0; i < MAX_SENSOR/2; i++)
          if (sensor[i].val == LOW) {
            status = false;
            break;
          }
        break;
      case 'r':
        for (int i = MAX_SENSOR/2; i < MAX_SENSOR; i++)
          if (sensor[i].val == LOW) {
            status = false;
            break;
          }
        break;
      default: status = false;
    }
    return status;
  }
};

#undef MAX_SENSOR

#endif
