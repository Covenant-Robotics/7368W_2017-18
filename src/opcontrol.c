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
        if (buttonGetState(JOY1_6U)) {
            blrsMotorSet(ARM_LEFT, 60, true);
            blrsMotorSet(ARM_RIGHT, 60, true);
        }
        else if(buttonGetState(JOY1_6D)) {
          blrsMotorSet(ARM_LEFT, -40, true);
          blrsMotorSet(ARM_RIGHT, -40, true);
        }
        else {
          blrsMotorSet(ARM_LEFT, 0, true);
          blrsMotorSet(ARM_RIGHT, 0, true);
        }

        delay(20);
    }
}
