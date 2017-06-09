#include "main.h"

static int clamp(int in) { return (abs(in) > 15) ? in : 0; }

void operatorControl() {
  int power;
  int turn;
    while (1) {
        power = clamp(joystickGetAnalog(1, 3)); // vertical axis on left joystick
        turn  = clamp(joystickGetAnalog(1, 1)); // horizontal axis on left joystick
        chassisSet(power + turn, power - turn);

        if (buttonIsNewPress(JOY1_8U)) {
          autonomous();
        }
        if (buttonGetState(JOY1_6D)) {
          blrsMotorSet(ARM_LEFT, 127, true);
          blrsMotorSet(ARM_RIGHT, 127, true);
        }
        else if(buttonGetState(JOY1_5U)) {
          blrsMotorSet(ARM_LEFT, -25, true);
          blrsMotorSet(ARM_RIGHT, -25, true);
        }
        else if(buttonGetState(JOY1_6U)) {
          blrsMotorSet(ARM_LEFT, 80, true);
          blrsMotorSet(ARM_RIGHT, 80, true);
        }
        else {
          blrsMotorSet(ARM_LEFT, 0, true);
          blrsMotorSet(ARM_RIGHT, 0, true);
        }

        delay(20);
    }
}
