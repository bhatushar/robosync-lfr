// Including required libraries
#include "MotorDriver.h"
#include "LineDetector.h"
#include "PIDController.h"

// Declaring global pins
  int motor_pins[] = {11,10,6,9}, // MotorL+, MotorL-, MotorR+, MotorR-
    lfr_dPins[] = {2, 3, 4, 5, 7, 8, 12, 13}, // Left to right
    lfr_aPin = A5; // Analog input pin on LSA08

// Global objects
MotorDriver motor(motor_pins);
LineDetector lfr(lfr_dPins, lfr_aPin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Calculating error and voltage
  int deviation = lfr.calcDeviation();
  int volt = PID(deviation);

  /*Serial.print("Deviation: ");
  Serial.println(deviation);
  //Serial.print(" ");
  Serial.print("Volt: ");
  Serial.println(volt);*/
  
  // Moving bot
  if (deviation < 22) {
    // Left
    //Serial.println("Left");
    motor.move('l', volt);
  } else if (deviation < 34) {
    // Slight Left
    //Serial.println("Slight Left");
    motor.move('l', volt, true);
  } else if (deviation < 36) {
    // Forward
    //Serial.println("Forward");
    motor.move('f', stdVolt);
  } else if (deviation < 49) {
    // Slight Right
    // Serial.println("Slight Right");
    motor.move('r', volt, true);
  } else {
    // Right
    //Serial.println("Right");
    motor.move('r', volt);
  }

  if (!lfr.isCrossSection()) {
    if (lfr.is90Turn('l'))
      motor.turn90('l');
    else if (lfr.is90Turn('l'))
       motor.turn90('r');
  }

  // TODO comment this when moving the bot*/
  // delay(1000);
}
