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
          motorSet(ARM_LEFT_BOTTOM, 127);
          motorSet(ARM_LEFT_TOP, 127);
        }
        else if(buttonGetState(JOY1_6D) == 1) {
          motorSet(ARM_LEFT_BOTTOM, -127);
          motorSet(ARM_LEFT_TOP, -127);
        }
        else
        motorSet(ARM_LEFT_BOTTOM, 0);
        motorSet(ARM_LEFT_TOP, 0);

    }
}
