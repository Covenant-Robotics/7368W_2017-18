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
 static fbc_t liftController;
 static fbc_pid_t lift_pid;
// static TaskHandle liftTask;
//
// int lift_positions[3] = {
//   LIFT_BOTTOM,
//   LIFT_TIP_CONE,
//   LIFT_TOP
// };
//
 static void _liftSet(int power) {
   blrsMotorSet(ARM_LEFT, power, false);
   blrsMotorSet(ARM_RIGHT, power, false);
 }

void liftInit() {
//   blrsMotorInit(ARM_LEFT, false, LIFT_SLEW, NULL);
//   blrsMotorInit(ARM_RIGHT, true, LIFT_SLEW, NULL);
   blrsMotorInit(ARM_LEFT, false, NULL, NULL);
   blrsMotorInit(ARM_RIGHT, true, NULL, NULL);
   blrsMotorInit(INTAKE, true, NULL, NULL);
   blrsMotorInit(CHAIN, false, NULL, NULL);
   blrsMotorInit(CLAW, false, NULL, NULL);

  // fbcInit(&liftController, _liftSet, liftGetPos, NULL, LIFT_NEG_DEADBAND, LIFT_POS_DEADBAND, LIFT_PID_TOL, LIFT_PID_CONF);
  // fbcPIDInitializeData(&lift_pid, LIFT_KP, 0, LIFT_KD, 0, 0);
  // fbcPIDInit(&liftController, &lift_pid);
 }

 void chainSetPos(int goal){
   if(analogRead(CHAIN_POT) < goal){
     blrsMotorSet(CHAIN, 80, true);
   }
   else if(analogRead(CHAIN_POT) > goal){
     blrsMotorSet(CHAIN, -60, true);
   }
   else {
     blrsMotorSet(CHAIN, 0, true);
   }
 }
void ChainRun(){
     if(buttonGetState(JOY1_8R)){
       chainSetPos(3000);             //tune this value for chain distance outside stack
   }
      if(buttonGetState(JOY1_8L)){
        chainSetPos(200);            //tune this value for chain distance while stacking
      }
}





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
