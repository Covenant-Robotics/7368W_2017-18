 /**
  * @file Lift Module
  */
 #include "lift.h"
 #include "main.h"
// <<<<<<< HEAD
// /*
// =======
//
// >>>>>>> master
// static fbc_t liftController;
// static fbc_pid_t lift_pid;
// static TaskHandle liftTask;
//
// int lift_positions[3] = {
//   LIFT_BOTTOM,
//   LIFT_TIP_CONE,
//   LIFT_TOP
// };
//

static fbc_t chainController;
static fbc_pid_t chainPid;

 // static void _liftSet(int power) {
 //   blrsMotorSet(ARM_LEFT, power, false);
 //   blrsMotorSet(ARM_RIGHT, power, false);
 // }
void chainSet(int power){
  blrsMotorSet(CHAIN, power, true);
}
int chainGetPos(){
  return analogRead(CHAIN_POT);
}
void liftInit() {
//   blrsMotorInit(ARM_LEFT, false, LIFT_SLEW, NULL);
//   blrsMotorInit(ARM_RIGHT, true, LIFT_SLEW, NULL);
   blrsMotorInit(ARM_LEFT, false, NULL, NULL);
   blrsMotorInit(ARM_RIGHT, true, NULL, NULL);
   blrsMotorInit(INTAKE, true, NULL, NULL);
   blrsMotorInit(CHAIN, true, NULL, NULL);
   blrsMotorInit(CLAW, false, NULL, NULL);
   fbcInit(&chainController, chainSet, chainGetPos, NULL, NULL, CHAIN_NEG_DEADBAND, CHAIN_POS_DEADBAND, CHAIN_PID_TOL, CHAIN_PID_CONF);
   fbcPIDInitializeData(&chainPid, CHAIN_KP, 0, CHAIN_KD, 0, 0);
   fbcPIDInit(&chainController,&chainPid);
  // fbcInit(&liftController, _liftSet, liftGetPos, NULL, LIFT_NEG_DEADBAND, LIFT_POS_DEADBAND, LIFT_PID_TOL, LIFT_PID_CONF);
  // fbcPIDInitializeData(&lift_pid, LIFT_KP, 0, LIFT_KD, 0, 0);
  // fbcPIDInit(&liftController, &lift_pid);
 }
 void chainSetPos(int goal){                //Function to set PID goal
   fbcSetGoal(&chainController, goal);
 }
void chainRun(){                            //Function to continuously use PID on chain
  fbcRunContinuous(&chainController);
}
void chainFindDeadband(){                   //Function for finding PID deadband
  fbcFindDeadband(&chainController, 50, uart1);
}
void chainPidAutotune(){

	// You might want to increase the goal from 50 something like 500-1000 depending on the range of the arm

  fbcPIDAutotune(&chainController, 3, 15, 3000, 50, uart1, 0, .7, 0, 0.001, 0, 0.01, 3, 5);
}

void coneTaskSet(void * parameter){
  blrsMotorSet(CLAW, -100, true);
  delay(200);
  blrsMotorSet(ARM_LEFT, 80, true);
  blrsMotorSet(ARM_RIGHT, 80, true);
  delay(200);
  blrsMotorSet(CLAW, 0, true);
  delay(500);
  blrsMotorSet(ARM_LEFT, 0, true);
  blrsMotorSet(ARM_RIGHT, 0, true);

  while(analogRead(CHAIN_POT < 3000)){
    blrsMotorSet(CHAIN, 80, true);
  }
  blrsMotorSet(CHAIN, 0, true);
  delay(20);
  while(analogRead(ARM_POT) < 790){
    blrsMotorSet(ARM_LEFT, -60, true);
    blrsMotorSet(ARM_RIGHT, -60, true);
  }
  blrsMotorSet(ARM_LEFT, 0, true);
  blrsMotorSet(ARM_RIGHT, 0, true);
}

 void coneTaskInitialize(){
   TaskHandle coneTaskHandle = taskCreate(coneTaskSet, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);//(coneTaskSet, 20);
   taskSuspend(coneTaskHandle);
 }


void chainTaskSet(){
  if(buttonGetState(JOY1_6U)) {   //Raise chain Pot value of 1300 is all the way up
    blrsMotorSet(CHAIN, -80, true);
  }
  else if(buttonGetState(JOY1_6D)){
    blrsMotorSet(CHAIN, 60, true);
  }
  while(JOY1_6U == 0 && JOY1_6D == 0){
    if(buttonGetState(JOY1_8R)){
       chainSetPos(3000);             //tune this value for chain distance outside stack
       blrsMotorSet(CHAIN, 0, true);
   }
      if(buttonGetState(JOY1_8L)){
        chainSetPos(200);            //tune this value for chain distance while stacking
        blrsMotorSet(CHAIN, 0, true);
      }
      else{
        blrsMotorSet(CHAIN, 0, true); //chain
      }
    delay(20);
  }
}
//TaskHandle chainTaskHandle = taskCreate(chainTaskSet, TASK_DEFAULT_STACK_SIZE,NULL, TASK_PRIORITY_DEFAULT);






//void ChainRun(){
//     if(buttonGetState(JOY1_8R)){
//       chainSetPos(3000);             //tune this value for chain distance outside stack
//   }
//      if(buttonGetState(JOY1_8L)){
//        chainSetPos(200);            //tune this value for chain distance while stacking
//      }
//}





//
// void liftStartTask() {
//   liftTask = fbcRunParallel(&liftController);
// }
//
// void liftEndTask() {
//   taskDelete(liftTask);
// }
//
// static void liftResumeTask() { taskResume(liftTask); }
// static void liftPauseTask() { taskSuspend(liftTask); }
//
// int liftGetPos() {
//   return analogRead(ARM_POT);
// }
//
// int liftGetSpeed() {
//   return motorGet(ARM_LEFT) & motorGet(ARM_RIGHT); //double check that the bitwise and works as expected
// }
//
// void liftOpSet(int power) {
//   // liftPauseTask();
//   if (power > 0 && liftGetPos() > LIFT_TOP)
//     power = 0;
//   else if (power < 0 && liftGetPos() < LIFT_BOTTOM)
//     power = 0;
//
//   _liftSet(power);
// }
//
// void liftPIDHold() {
//   int cur_pos = liftGetPos();
//   fbcSetGoal(&liftController, cur_pos);
//   liftResumeTask();
// }
//
// void liftIncrementPos() {
//   int cur_pos = liftGetPos();
//   fbcSetGoal(&liftController, cur_pos + LIFT_INCREMENT_DELTA);
//   liftResumeTask();
// }
//
// void liftDecrementPos() {
//   int cur_pos = liftGetPos();
//   fbcSetGoal(&liftController, cur_pos - LIFT_INCREMENT_DELTA);
//   liftResumeTask();
// }
//
// void liftSnapToPos() {
//   int diff, prev_diff = ~0;
//   int sp_num = 0;
//   int cur_pos = liftGetPos();
//   for (int i = 0; i < (int)(sizeof(lift_positions) / sizeof(int)); i++) {
//     diff = lift_positions[i] - cur_pos;
//     if (abs(diff) < abs(prev_diff))
//       sp_num = i;
//     prev_diff = lift_positions[sp_num] - cur_pos;
//   }
//   fbcSetGoal(&liftController, lift_positions[sp_num]);
//   liftResumeTask();
// }
//
// void liftPID() {
//   fbcRunContinuous(&liftController);
// }
//
// void liftSetPos(int pos) {
//   fbcSetGoal(&liftController, pos);
// <<<<<<< HEAD
// } */
// =======
// }
// >>>>>>> master
