#ifndef LINEDETECTOR_H
#define LINEDETECTOR_H

#define MAX_SENSOR 8

struct IRSensor {
  int pin,      // The pin to which the sensor is connected
      weight,   // The weight assigned to each pin
      val;
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

    // Return value read from analog pin
    return analogRead(analogPin);
  }

  int isCrossSection() {
    /*
    Function to check if the bot is at a cross section using the weight of the sensors
    */
    if(zeroSensor == MAX_SENSOR) {
      // All sensors have zero weight
      zeroSensor = 0;
      return 1;
    }
    else {
      zeroSensor = 0;
      return 0;
    }
  }

  int is90Turn() {
    int is90 = 1;
    for(int i = 0; i < MAX_SENSOR/2; i++)
      if (sensor[i].val == 1) {
        is90 = 0;
        break;
      }
    if (!is90)
      for (int i = MAX_SENSOR/2; i < MAX_SENSOR; i++)
        if (sensor[i].val == 1) {
        is90 = 0;
        break;
      }
    return is90;
  }

  int is120Junction() {
  	int pattern[3][8] = {
  		{0, 0, 0, 1, 1, 0, 0, 0},
  		{1, 0, 1, 1, 0, 0, 0, 0},
  		{0, 0, 0, 0, 1, 1, 0, 1}
  	};
	for (int i = 0; i < 3; i++) {
		int matched = 1;
		for (int j = 0; j < 8; j++)
			if (pattern[i][j] != sensor[j].val) {
				matched = 0;
				break;
			}
		if (matched == 1) return 1;
	}
	return 0;
  }
};

#undef MAX_SENSOR

#endif
