// Including required libraries
#include "MotorDriver.h"
#include "LineDetector.h"
#include "PIDController.h"

// Declaring global pins
  int motor_pins[] = {11,10,6,9}, // MotorL+, MotorL-, MotorR+, MotorR-
    lfr_dPins[] = {2, 3, 4, 5, 7, 8, 12, 13}, // Left to right
    // TODO set pin number
    lfr_aPin = A5; // Analog input pin on LSA08

// Global objects
MotorDriver motor(motor_pins);
LineDetector lfr(lfr_dPins, lfr_aPin);

int lastDeviation = 0; // Variable to store deviation calculated in previous cycle

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Calculating error and voltage
  int deviation = lfr.calcDeviation();
  int volt = PID(abs(deviation - 35), lastDeviation);

  Serial.print("Deviation: ");
  Serial.println(deviation);
  Serial.print("Volt: ");
  Serial.println(volt);
  
  // Moving bot
  // TODO check if left and right needs to be swapped 
  if(deviation < 35) {
    // Right
    Serial.println("Right");
    motor.move('r', volt);
  }
  else if(deviation > 35) {
    // Left
    Serial.println("Left");
    motor.move('l', volt);
  }
  else {
    // Forward
    Serial.println("Forward");
    motor.move('f', stdVolt);
  }

  // Storing current deviation for future use
  lastDeviation = abs(deviation - 35);

  // TODO comment this when moving the bot
  
}
