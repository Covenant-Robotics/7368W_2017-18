#include "main.h"

static int clamp(int in) { return (abs(in) > 15) ? in : 0; }

void operatorControl() {
    bool tank = false;
    while (1) {
      if (buttonIsNewPress(JOY1_7L))
        tank = !tank;

      if (tank) {
        int left = clamp(joystickGetAnalog(1, 3));
        int right = clamp(joystickGetAnalog(1, 2));
        chassisSet(left,right);
      }
      else {
        int power = clamp(joystickGetAnalog(1, 3)); // vertical axis on left joystick
        int turn  = clamp(joystickGetAnalog(1, 1)); // horizontal axis on left joystick
        chassisSet(power + turn, power - turn);
      }

//        if (buttonIsNewPress(JOY1_8U)) {
  //        autonomous();
//        }

        if(buttonGetState(JOY1_5U)) {
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
        if (buttonGetState(JOY1_6D)) {
          blrsMotorSet(INTAKE, 80, true);
        }
        else if(buttonGetState(JOY1_5D)) {
          blrsMotorSet(INTAKE, -80, true);
        }
        else {
          blrsMotorSet(INTAKE, 0, true);
        }

        if(buttonGetState(JOY1_7U)) {
          blrsMotorSet(CHAIN, 50, true);
          blrsMotorSet(CHAIN, 50, true);
        }
        else if(buttonGetState(JOY1_7D)){
          blrsMotorSet(CHAIN, -40, true);
          blrsMotorSet(CHAIN, -40, true);
        }
        else{
          blrsMotorSet(CHAIN, 0, true);
          blrsMotorSet(CHAIN, 0, true);
        }
        if(buttonGetState(JOY1_8U)){
          blrsMotorSet(CLAW, 60, true);
          blrsMotorSet(CLAW, 60, true);
        }
        else if(buttonGetState(JOY1_8D)){
          blrsMotorSet(CLAW, -60, true);
          blrsMotorSet(CLAW, -60, true);
        }
        else{
          blrsMotorSet(CLAW, 0, true);
          blrsMotorSet(CLAW, 0, true);
        }
        delay(20);
    }
}
