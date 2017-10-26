/**
 * @file Lift Rebuild
 */
#include "main.h"

//size of the array should be the number of cones that the bot can stack
int armPositions[13] = { 1450, 1400, 1480, 1375, 1270, 1165, 1060, 955, 850, 745, 640, 535, 430 };

static fbc_t chainController, armController;
static fbc_pid_t chainPid, armPID;

// void chainSet(int power) {
//   blrsMotorSet(CHAIN, power, true);
// }

//}

// void liftSet(int power) {
// 	blrsMotorSet(ARM_LEFT, power, true);
//   blrsMotorSet(ARM_RIGHT, power, true);
// }

static void _pidLiftSet(int power) {
	liftSet(-power);
}

int liftGetPos() {
	return analogRead(ARM_POT);;
}

void liftSetPos(int goal) {
	fbcSetGoal(&armController, goal);
}

void clawSet(int power) {
	blrsMotorSet(CLAW, power, true);
}

void mogoSet(int power) {
	blrsMotorSet(INTAKE, power, true);
}

// void liftInit() {
//    blrsMotorInit(ARM_LEFT, false, NULL, NULL);
//    blrsMotorInit(ARM_RIGHT, true, NULL, NULL);
//    blrsMotorInit(INTAKE, true, NULL, NULL);
//    blrsMotorInit(CHAIN, true, NULL, NULL);
//    blrsMotorInit(CLAW, false, NULL, NULL);
//
//    fbcInit(&chainController, chainSet, chainGetPos, NULL, fbcStallDetect, CHAIN_NEG_DB_STACK, CHAIN_POS_DB_STACK, CHAIN_PID_TOL, CHAIN_PID_CONF);
//    fbcPIDInitializeData(&chainPid, CHAIN_KP, 0, CHAIN_KD, 0, 0);
//    fbcPIDInit(&chainController,&chainPid);
//
// 	 fbcInit(&armController, _pidLiftSet, liftGetPos, NULL, NULL, LIFT_NEG_DEADBAND, LIFT_NEG_DEADBAND, LIFT_PID_TOL, LIFT_PID_CONF);
// 	 fbcPIDInitializeData(&armPID, LIFT_KP, 0, LIFT_KD, 0, 0);
// 	 fbcPIDInit(&armController, &armPID);
//  }

 // void chainSetPos(int goal) {
 //  fbcSetGoal(&chainController, goal);
 // }

 // void chainRun() {
 //   fbcRunContinuous(&chainController);
 // }

 void liftToDriverLoad() {
	 if (armController.goal != LIFT_DRIVER_POS) {
		 fbcSetGoal(&armController, LIFT_DRIVER_POS);
	 }
	 fbcRunContinuous(&armController);
 }

/**
 * @brief Autostacker
 */
/*
// Sequence - Lift up, chain back, claw open, chain forward, lift down

// Attempt at running without a task
unsigned long stack_timer_start = 0, stack_timer;
// flags to indicate which part of the movement that the arm is in
bool lift1 = false, lift2 = false, chain1 = false, chain2 = false, claw_opened = false;

typedef enum { START, LIFT_UP, CHAIN_STACKING, CLAW_OPEN, CHAIN_INTAKING, LIFT_DOWN} stack_state_e;
stack_state_e state = START;
void stack(unsigned int height, bool start) {
	stack_timer = millis() - stack_timer_start;

	if (start) state == START;

	if (state == START) {
		fbcSetGoal(&armController, armPositions[height]);
		state = LIFT_UP;
	}
	else if (state == LIFT_UP && fbcIsConfident(&armController)) {
		//lift has finished, start chainbar
		armController.move(0);
		// fbcSetGoal(&chainController, CHAIN_STACK);
		// chainController.pos_deadband = CHAIN_POS_DB_STACK;
		// chainController.neg_deadband = CHAIN_NEG_DB_STACK;
		state = CHAIN_STACKING;
	}
	else if (state == CHAIN_STACKING && chainController.sense() < CHAIN_STACK) {
		//chainbar finished, start claw
		chainController.move(40);
		stack_timer_start = millis();
		state = CLAW_OPEN;
	}
	else if (state == CLAW_OPEN && stack_timer > 1500) {
		clawSet(0);
		fbcSetGoal(&chainController, CHAIN_INTAKE);
		chainController.pos_deadband = CHAIN_POS_DB_INTAKE;
		chainController.neg_deadband = CHAIN_NEG_DB_INTAKE;
		state = CHAIN_INTAKING;
	}
	else if (state == CHAIN_INTAKING && chainController.sense() > CHAIN_INTAKE) {
		chainController.move(0);
		fbcSetGoal(&armController, armPositions[0]);
		state = LIFT_DOWN;
	}
	else if (state == LIFT_DOWN && fbcIsConfident(&armController)) {
		armController.move(0);
		return;
	}

	if (state == LIFT_UP || state == LIFT_DOWN)
		fbcRunContinuous(&armController);
	else if (state == CHAIN_STACKING)
		chainSet(-60);
	else if (state == CHAIN_INTAKING)
		chainSet(70);
	else if (state == CLAW_OPEN)
		clawSet(-100);
}
*/
/**
 * Sorta autostacking code, just raises then lowers the lift to get around the cone
 *
 * Going to try running this as a task since that was easier to explain
 */
#define LIFT_UP_DELTA 100 //how much the lift needs to go up to clear the cone
bool start; //true if the macro should restart
TaskHandle autoReturnTask;

void _returnToIntaking(void* param) {
	int cur = 0;
MACRO_START:
	cur = armController.goal;
	fbcSetGoal(&armController, cur - LIFT_UP_DELTA);
	while (!fbcIsConfident(&armController)) {
		fbcRunContinuous(&armController);
		delay(20);
	}
	while (chainGetPos() > CHAIN_INTAKE) {
		chainSet(80);
		fbcRunContinuous(&armController); // to guarantee that it will stay in the same place
		delay(20);
	}
	fbcSetGoal(&armController, armPositions[0]);
	chainSet(0);
	while (!fbcIsConfident(&armController)) {
		fbcRunContinuous(&armController);
		delay(20);
	}
	while (true) {
		if (start)
			goto MACRO_START;
		delay(20);
	}
}

void liftAutoReturnTaskInit() {
	autoReturnTask = taskCreate(_returnToIntaking, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void liftAutoReturnSuspend() {
	if (taskGetState(autoReturnTask) != TASK_SUSPENDED)
		taskSuspend(autoReturnTask);
}

void liftAutoReturnResume() {
	if (taskGetState(autoReturnTask) == TASK_SUSPENDED) {
		start = true;
		taskResume(autoReturnTask);
	}
}
