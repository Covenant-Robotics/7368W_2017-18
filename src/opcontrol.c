#include "main.h"
void operatorControl() {
  int power;
  int turn;
    while (1) {
        power = joystickGetAnalog(1, 3); // vertical axis on left joystick
        turn  = joystickGetAnalog(1, 1); // horizontal axis on left joystick
        chassisSet(power + turn, power - turn);
        delay(20);
        if (buttonIsNewPress(JOY1_8U)) {
          autonomous();
        }
        if (buttonGetState(JOY1_6U) == 1) {
            blrsMotorSet(ARM_LEFT, 127, true);
            blrsMotorSet(ARM_RIGHT, 127, true);
        }
        else if(buttonGetState(JOY1_6D) == 1) {
          blrsMotorSet(ARM_LEFT, -127, true);
          blrsMotorSet(ARM_RIGHT, -127, true);
        }
        else
        blrsMotorSet(ARM_LEFT, 0, true);
        blrsMotorSet(ARM_RIGHT, 0, true);

    }
}
