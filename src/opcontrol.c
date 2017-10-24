#include "main.h"

static int clamp(int in) { return (abs(in) > 15) ? in : 0; }   //Deadband used for Joystick to reduce noise while not moving

#define MANUAL 0
#define AUTOSTACK 1
#define DRIVER_LOADS 2

void operatorControl() {
	int arm_state = MANUAL;
	unsigned int stack_height = 0;
	liftAutoReturnTaskInit();
	while (true) {

		//TODO: Add a check for the mobile goal intake to keep from sending power if the lift is in its path

		// Drivetrain Controls
		int power = clamp(joystickGetAnalog(1, 3)); // vertical axis on left joystick
		int turn  = clamp(joystickGetAnalog(1, 1)); // horizontal axis on left joystick
		chassisSet(power + turn, power - turn);

		// Mogo Manual Controls
		if (buttonGetState(JOY1_8L)) {
			mogoSet(-80);
		}
		else if (buttonGetState(JOY1_8R)) {
			mogoSet(80);
		}
		else {
			mogoSet(0);
		}

		// Lift Manual Controls
		if (buttonGetState(JOY1_5U)) {
			arm_state = MANUAL;
			liftSet(80);
		}
		else if (buttonGetState(JOY1_5D)) {
			arm_state = MANUAL;
			liftSet(-45);
		}
		else if (arm_state == MANUAL) {
			liftSet(0);
		}

		// ChainBar Manual Controls
		if (buttonGetState(JOY1_6U)) {
			arm_state = MANUAL;
			chainSet(-60);
		}
		else if (buttonGetState(JOY1_6D)) {
			arm_state = MANUAL;
			chainSet(80);
		}
		else if (arm_state == MANUAL) {
			chainSet(0);
		}

		// Claw Manual Controls
		if (buttonGetState(JOY1_8D)) {
			arm_state = MANUAL;
			clawSet(-100);
		}
		else if (arm_state == MANUAL) {
			clawSet(0);
		}

		// Autostacking
		if (buttonGetState(JOY1_7U)) {
			arm_state = AUTOSTACK;
		}
		else if (buttonGetState(JOY1_8U)) {
			arm_state = DRIVER_LOADS;
		}

		// Stack Height Counting
		if (buttonIsNewPress(JOY1_7R)) {
			stack_height++;
		}
		else if (buttonIsNewPress(JOY1_7L)) {
			stack_height--;
		}
		else if (buttonIsNewPress(JOY1_7D)) {
			stack_height = 0;
		}

		// // Background Arm Movement
		// if (arm_state == AUTOSTACK) {
		// 	// Will probably also need to pass in an argument to specify if the autostacker should go to the ground
		// 	// or the driver load station
		// 	stack(stack_height + 1, stack_start);
		// }
		// else if (arm_state == DRIVER_LOADS) {
		// 	liftToDriverLoad();
		// }
		if (arm_state == AUTOSTACK)
			liftAutoReturnResume();
		else if (arm_state == MANUAL)
			liftAutoReturnSuspend();

		delay(20);
	}
}

/*
void operatorControl() {

    bool tank = false;
    bool manual = true;
    while (1) {
      lcdPrint(uart1, 1, "Pot Value: %d", analogRead(CHAIN_POT));
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if (buttonIsNewPress(JOY1_7R)) {              //testing to find deadband of PID loops, PID autotune, or run Autonomous
//          chainPidAutotune();
          chainFindDeadband();
//                autonomous();
        }
        if (buttonIsNewPress(JOY1_8U)){
      //    taskResume(coneResetTask)
					coneResetTask();
					delay(20);
					taskSuspend(coneResetTask());
        }
				// else {
				// 	taskSuspend(coneResetTask());
				// }
        if (analogRead(CHAIN_POT) < 600 && !buttonGetState(JOY1_6U) && !buttonGetState(JOY1_8L) && !buttonGetState(JOY1_8R) ){
          blrsMotorSet(CHAIN, 30, true);
        }
        else if(buttonGetState(JOY1_6U)){            //Button 6U for manual up control of Chain bar
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if (buttonGetState(JOY1_7U)) {      //Button 7U for going out mogo intake
  blrsMotorSet(INTAKE, 80, true);
}
else if(buttonGetState(JOY1_7D)) {  //Button 7D for bringing in mogo intake
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
*/
