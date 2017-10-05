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

//       if (buttonIsNewPress(JOY1_8U)) {
  //        autonomous();
//        }

        if(buttonGetState(JOY1_5D)) {
          blrsMotorSet(ARM_LEFT, -45, true);  //Lower Arm
          blrsMotorSet(ARM_RIGHT, -45, true);
        }
        else if(buttonGetState(JOY1_5U)) {  //Raise Arm
          blrsMotorSet(ARM_LEFT, 80, true);
          blrsMotorSet(ARM_RIGHT, 80, true);
        }
        else {
          blrsMotorSet(ARM_LEFT, 0, true);  //Arm =0
          blrsMotorSet(ARM_RIGHT, 0, true);
        }


        if (buttonGetState(JOY1_7U)) {  //Going out Intake
          blrsMotorSet(INTAKE, 80, true);
        }
        else if(buttonGetState(JOY1_7D)) {  //Bringing In Intake
          blrsMotorSet(INTAKE, -80, true);
        }
        else {
          blrsMotorSet(INTAKE, 0, true);  //Intake =0
        }


        if(buttonGetState(JOY1_6U)) {   //Raise chain Pot value of 1300 is all the way up
          blrsMotorSet(CHAIN, 80, true);
        }
        else if(buttonGetState(JOY1_6D)){ //Lower chain Pot value of 7 is all the way down...broekn Pots??
          blrsMotorSet(CHAIN, -60, true);
        }
        else{
          blrsMotorSet(CHAIN, 0, true); //chain
        }


        if(buttonGetState(JOY1_8U)){  //Open Claw
          blrsMotorSet(CLAW, 127, true);
        }
        else if(buttonGetState(JOY1_8D)){ //Close claw
          blrsMotorSet(CLAW, -100, true);
        }
        else{
          blrsMotorSet(CLAW, 0, true);  //Claw =0
        }
        if(buttonGetState(JOY1_8R)){
           chainSetPos(3000);             //tune this value for chain distance outside stack
           blrsMotorSet(CHAIN, 0, true); //chain
       }
          if(buttonGetState(JOY1_8L)){
            chainSetPos(200);            //tune this value for chain distance while stacking
            blrsMotorSet(CHAIN, 0, true); //chain
          }


       printf("Chain Pot %d\n", analogRead(CHAIN_POT));
        delay(20);
    }
}
