#include "main.h"

static int clamp(int in) { return (abs(in) > 15) ? in : 0; }   //Deadband used for Joystick to reduce noise while not moving

void operatorControl() {
    bool tank = false;
    bool manual = true;
    while (1) {
      if (buttonIsNewPress(JOY1_7L))                //Button 7L changes Drive type
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

      if (buttonIsNewPress(JOY1_7R)) {              //testing to find deadband of PID loops
          chainPidAutotune();
//          chainFindDeadband();
//                autonomous();
        }

        if(buttonGetState(JOY1_6U)){            //Button 6U for manual up control of Chain bar
          manual=true;
          blrsMotorSet(CHAIN, 80, true);
        }
        else if(buttonGetState(JOY1_6D)){       //Button 6D for manual down control of Chain bar
          manual=true;
          blrsMotorSet(CHAIN, -60, true);
        }
        else if(buttonIsNewPress(JOY1_8R)){     //Button 8R used for PID attach to out pos. of Chain bar
          manual=false;
          chainSetPos(3000);                  //out Potentiometer value
        }
        else if(buttonIsNewPress(JOY1_8L)){     //Button 8L used for PID attach to in pos. of Chain bar
          manual=false;
          chainSetPos(200);                   // in Potentiometer value
        }
        else if(manual){
          blrsMotorSet(CHAIN, 0, true);
        }
        else
        chainRun();                           //run PID continuously until next input

        if(buttonGetState(JOY1_5D)) {         //Button 5D for lowering arm
          blrsMotorSet(ARM_LEFT, -45, true);
          blrsMotorSet(ARM_RIGHT, -45, true);
        }
        else if(buttonGetState(JOY1_5U)) {   //Button 5U for raising Arm
          blrsMotorSet(ARM_LEFT, 80, true);
          blrsMotorSet(ARM_RIGHT, 80, true);
        }
        else {
          blrsMotorSet(ARM_LEFT, 0, true);  //Arm =0
          blrsMotorSet(ARM_RIGHT, 0, true);
        }


        if (buttonGetState(JOY1_7U)) {      //Button 7U for going out mogo intake
          blrsMotorSet(INTAKE, 80, true);
        }
        else if(buttonGetState(JOY1_7D)) {  //Button 7D for bringing in mogo intake
          blrsMotorSet(INTAKE, -80, true);
        }
        else {
          blrsMotorSet(INTAKE, 0, true);    //Intake =0
        }

        if(buttonGetState(JOY1_8U)){        //Button 8U for Open Claw
          blrsMotorSet(CLAW, 127, true);
        }
        else if(buttonGetState(JOY1_8D)){   //Button 8D for Close claw
          blrsMotorSet(CLAW, -100, true);
        }
        else{
          blrsMotorSet(CLAW, 0, true);     //Claw =0
        }

        delay(20);
    }
}
