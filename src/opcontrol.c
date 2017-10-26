#include "main.h"

static int clamp(int in) { return (abs(in) > 15) ? in : 0; }   //Deadband used for Joystick to reduce noise while not moving

#define MANUAL 0
#define AUTOSTACK 1                           //different states for the arm
#define DRIVER_LOADS 2

void operatorControl() {                       //start of opcontrol function

int arm_state = MANUAL;                         //initializes arm state
liftAutoReturnTaskInit();                       //initializes autoReturnTask

while (1) {                                       //start of opcontrol while loop
  lcdPrint(uart1, 1, "encoder: %d", chassisLeftPos() );
  lcdPrint(uart1, 2, "batterY %d", powerLevelMain());
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int power = clamp(joystickGetAnalog(1, 3)); // vertical axis on left joystick
int turn  = clamp(joystickGetAnalog(1, 1)); // horizontal axis on right joystick
chassisSet(power + turn, power - turn);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 if(buttonGetState(JOY1_6U) && analogRead(CHAIN_POT) < 3000){            //Button 6U for manual out control of Chain bar
  arm_state = MANUAL;
  blrsMotorSet(CHAIN, 80, true);
}
else if(buttonGetState(JOY1_6D) && analogRead(CHAIN_POT) > 10){       //Button 6D for manual in control of Chain bar
  arm_state = MANUAL;
  blrsMotorSet(CHAIN, -60, true);
}
else if(arm_state == MANUAL){
  blrsMotorSet(CHAIN, 0, true);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(buttonGetState(JOY1_5D)) {         //Button 5D for lowering arm
  arm_state = MANUAL;
  liftSet(-45);
}
else if(buttonGetState(JOY1_5U)) {   //Button 5U for raising Arm
  arm_state = MANUAL;
  liftSet(80);
}
else if(arm_state == MANUAL){
  liftSet(0);
}

if (buttonGetState(JOY1_8U)) {          //start autoReturnTask
			arm_state = AUTOSTACK;
		}
if (arm_state == AUTOSTACK)             //actually does start autoReturnTask (NOT WORKING)
  liftAutoReturnResume();
else if (arm_state == MANUAL)           //suspends autoReturnTask if in manual control
  liftAutoReturnSuspend();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if (buttonGetState(JOY1_7U) && analogRead(ARM_POT) < 1400) {      //Button 7U for going out mogo intake
  blrsMotorSet(INTAKE, 80, true);
}
else if(buttonGetState(JOY1_7D) && analogRead(ARM_POT) < 1400) {  //Button 7D for bringing in mogo intake
  blrsMotorSet(INTAKE, -80, true);
}
else {
  blrsMotorSet(INTAKE, 0, true);    //Intake =0
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(buttonGetState(JOY1_8D)){   //Button 8D for open claw
  blrsMotorSet(CLAW, -100, true);
  }
else{
  blrsMotorSet(CLAW, 0, true);     //Claw =0
    }

      delay(20);
    }
}
