/**
 * @file Lift Rebuild
 */
#include "main.h"

//size of the array should be the number of cones that the bot can stack
int armPositions[13] = { 1670, 1585, 1480, 1375, 1270, 1165, 1060, 955, 850, 745, 640, 535, 430 };

static fbc_t chainController, armController;
static fbc_pid_t chainPid, armPID;

void chainSet(int power) {
  blrsMotorSet(CHAIN, power, true);
}

int chainGetPos() {
  return analogRead(CHAIN_POT);
}

void liftSet(int power) {
	blrsMotorSet(ARM_LEFT, power, true);
  blrsMotorSet(ARM_RIGHT, power, true);
}

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

void liftInit() {
   blrsMotorInit(ARM_LEFT, false, NULL, NULL);
   blrsMotorInit(ARM_RIGHT, true, NULL, NULL);
   blrsMotorInit(INTAKE, true, NULL, NULL);
   blrsMotorInit(CHAIN, true, NULL, NULL);
   blrsMotorInit(CLAW, false, NULL, NULL);

   fbcInit(&chainController, chainSet, chainGetPos, NULL, NULL, CHAIN_NEG_DEADBAND, CHAIN_POS_DEADBAND, CHAIN_PID_TOL, CHAIN_PID_CONF);
   fbcPIDInitializeData(&chainPid, CHAIN_KP, 0, CHAIN_KD, 0, 0);
   fbcPIDInit(&chainController,&chainPid);

	 fbcInit(&armController, _pidLiftSet, liftGetPos, NULL, NULL, LIFT_NEG_DEADBAND, LIFT_NEG_DEADBAND, LIFT_PID_TOL, LIFT_PID_CONF);
	 fbcPIDInitializeData(&armPID, LIFT_KP, 0, LIFT_KD, 0, 0);
	 fbcPIDInit(&armController, &armPID);
 }

 void chainSetPos(int goal) {
	 fbcSetGoal(&chainController, goal);
 }

 void chainRun() {
   fbcRunContinuous(&chainController);
 }

 void liftToDriverLoad() {
	 if (armController.goal != LIFT_DRIVER_POS) {
		 fbcSetGoal(&armController, LIFT_DRIVER_POS);
	 }
	 fbcRunContinuous(&armController);
 }

/**
 * @brief Autostacker
 */

// Sequence - Lift up, chain back, claw open, chain forward, lift down

// Attempt at running without a task
unsigned long stack_timer_start = 0, stack_timer;
// flags to indicate which part of the movement that the arm is in
bool lift1 = false, lift2 = false, chain1 = false, chain2 = false, claw_opened = false;

typedef enum { START, LIFT_UP, CHAIN_STACKING, CLAW_OPEN, CHAIN_INTAKING, LIFT_DOWN} stack_state_e;
stack_state_e state = START;
void stack(unsigned int height) {
	stack_timer = millis() - stack_timer_start;

	if (state == START) {
		fbcSetGoal(&armController, armPositions[height]);
		state = LIFT_UP;
	}
	else if (state == LIFT_UP && fbcIsConfident(&armController)) {
		//lift has finished, start chainbar
		fbcSetGoal(&chainController, CHAIN_STACKING);
		state = CHAIN_STACKING;
	}
	else if (state == CHAIN_STACKING && fbcIsConfident(&chainController)) {
		stack_timer_start = millis();
		state = CLAW_OPEN;
	}
	else if (state == CLAW_OPEN && stack_timer > 1000) {
		clawSet(0);
		fbcSetGoal(&chainController, CHAIN_INTAKE);
		state = CHAIN_INTAKING;
	}
	else if (state == CHAIN_INTAKING && fbcIsConfident(&chainController)) {
		fbcSetGoal(&armController, armPositions[0]);
		state = LIFT_DOWN;
	}

	if (state == LIFT_UP || state == LIFT_DOWN)
		fbcRunContinuous(&armController);
	else if (state == CHAIN_INTAKING || state == CHAIN_STACKING)
		fbcRunContinuous(&chainController);
	else if (state == CLAW_OPEN)
		clawSet(-100);
}
/*
void stack(unsigned int height) {
	stack_timer = millis();
	unsigned long cur_time = stack_timer - stack_timer_start;

	// Raise the lift
	if (!lift1) {
		clawSet(0);
		fbcSetGoal(&armController, armPositions[height]);
		lift1 = true;
	}
	else if (!fbcIsConfident(&armController))
		fbcRunContinuous(&armController);

	// Then run the chainbar
	else if (!chain1) {
		fbcSetGoal(&chainController, CHAIN_STACK);
		chain1 = true;
	}
	else if (!fbcIsConfident(&chainController))
		fbcRunContinuous(&chainController);

	// Open the claw
	else if (!claw_opened) {
		stack_timer_start = millis();
		claw_opened = true;
	}
	else if (cur_time < 1000)
		clawSet(100);

	// Run the chainbar back to intake position
	else if (!chain2) {
		fbcSetGoal(&chainController, CHAIN_INTAKE);
		clawSet(0);
		chain2 = true;
	}
	else if (!fbcIsConfident(&chainController))
		fbcRunContinuous(&chainController);

	//Set the lift back down
	else if (!lift2) {
		fbcSetGoal(&armController, armPositions[0]);
		lift2 = true;
	}
	else if (!fbcIsConfident(&armController))
		fbcRunContinuous(&armController);

	// Clear the flags
	lift1 = false; lift2 = false; chain1 = false; chain2 = false; claw_opened = false;
}
*/

/*
typedef enum { CLAW_CLOSE, LIFT_UP, CHAIN_STACKING, CLAW_OPEN, CHAIN_INTAKING, LIFT_DOWN} stack_state_e;
stack_state_e state;
bool running = false;
unsigned long cur_time = 0;
void stack_alt() {
	if (running) {
		// Check to see if still running
		if ((state == CLAW_CLOSE || state == CLAW_OPEN) && cur_time > 1000)
	}
}
*/
