#include "main.h"

static int clamp(int in) { return (abs(in) > 15) ? in : 0; }   //Deadband used for Joystick to reduce noise while not moving

#define MANUAL 0
#define AUTOSTACK 1                           //different states for the arm
#define DRIVER_LOADS 2

#define MOGO_STAY 0
#define MOGO_OUT 1
#define MOGO_IN 2

void operatorControl() {                       //start of opcontrol function

int arm_state = MANUAL;                         //initializes arm state
liftAutoReturnTaskInit();                       //initializes autoReturnTask

int auto_mogo = MOGO_STAY;

while (1) {                                       //start of opcontrol while loop
//  lcdPrint(uart1, 1, "encoder: %d", chassisLeftPos() );
  lcdPrint(uart1, 1, "battery %d", powerLevelMain());
  lcdPrint(uart1, 2, "bar pot %d", analogRead(BAR_POT));
//   mogoTasksInit(); //initialize the tasks
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int power = clamp(joystickGetAnalog(1, 3)); // vertical axis on left joystick
int turn  = clamp(joystickGetAnalog(1, 4)); // horizontal axis on right joystick
chassisSet(power + turn, power - turn);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 if(buttonGetState(JOY1_6U) && analogRead(CHAIN_POT) < 3000){            //Button 6U for manual out control of Chain bar
  arm_state = MANUAL;
  blrsMotorSet(CHAIN, 80, false);
}
else if(buttonGetState(JOY1_6D) && analogRead(CHAIN_POT) > 12){       //Button 6D for manual in control of Chain bar
  arm_state = MANUAL;
  blrsMotorSet(CHAIN, -60, false);
}
else if(arm_state == MANUAL){
  blrsMotorSet(CHAIN, 0, false);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(buttonGetState(JOY1_5D)) {         //Button 5D for lowering arm
  arm_state = MANUAL;
  liftSet(-70);
}
else if(buttonGetState(JOY1_5U)) {   //Button 5U for raising Arm
  arm_state = MANUAL;
  liftSet(80);
}
else if(arm_state == MANUAL){
  liftSet(0);
}

// if (buttonGetState(JOY1_8U)) {          //start autoReturnTask
// 			arm_state = AUTOSTACK;
// 		}
if (arm_state == AUTOSTACK)             //actually does start autoReturnTask (NOT WORKING)
  liftAutoReturnResume();
else if (arm_state == MANUAL)           //suspends autoReturnTask if in manual control
  liftAutoReturnSuspend();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

if (buttonGetState(JOY1_8R) && analogRead(ARM_POT) < 1400) {
  blrsMotorSet(INTAKE, 80, true);
  blrsMotorSet(INTAKE2, 80, true);
	auto_mogo = MOGO_OUT;
}
else if(buttonGetState(JOY1_8L) && analogRead(ARM_POT) < 1400) {
  blrsMotorSet(INTAKE, -80, true);
  blrsMotorSet(INTAKE2, -80, true);
	auto_mogo = MOGO_IN;
}
else if (buttonGetState(JOY1_7U) && analogRead(ARM_POT) < 1400) {
	blrsMotorSet(INTAKE, 80, true);
  blrsMotorSet(INTAKE2, 80, true);
	auto_mogo = MOGO_STAY;
}
else if (buttonGetState(JOY1_7D) && analogRead(ARM_POT) < 1400) {
		blrsMotorSet(INTAKE, -80, true);
    blrsMotorSet(INTAKE2, -80, true);
		auto_mogo = MOGO_STAY;
}
else if (buttonGetState(JOY1_8L) && buttonGetState(JOY1_8R)) {
	// Stop the automatic movement if both buttons are pressed
	// This probably isn't the easiest way to cancel the movement for the driver but since I don't know what your
	// control scheme is like this seemed like a good placeholder. change this to a dedicated killswitch button if
	// you want
	blrsMotorSet(INTAKE, 0, true);
	auto_mogo = MOGO_STAY;
}
else if (auto_mogo == MOGO_OUT && analogRead(MOGO_POT) > 650) {
	blrsMotorSet(INTAKE, 127, true);
	blrsMotorSet(INTAKE2, 127, true);
}
else if (auto_mogo == MOGO_IN && analogRead(MOGO_POT) < 2900) {
	blrsMotorSet(INTAKE, -127, true);
	blrsMotorSet(INTAKE2, -127, true);
}
else {
  blrsMotorSet(INTAKE, 0, true);
	blrsMotorSet(INTAKE2, 0, true);
	auto_mogo = MOGO_STAY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(buttonGetState(JOY1_8D)){   //Button 8D for open claw
  blrsMotorSet(CLAW, -75, true);
  }
else if(buttonGetState(JOY1_8U)){ //Button 8U for close claw
  blrsMotorSet(CLAW, 100, true);
}
else{
  blrsMotorSet(CLAW, 0, true);     //Claw =0
    }

      delay(20);
    }
}
