#include "lift.h"

void liftInit(){
  blrsMotorInit(ARM_LEFT, false, NULL, NULL);
  blrsMotorInit(ARM_RIGHT, true, NULL, NULL);
}

void liftSet(int power){
  blrsMotorSet(ARM_LEFT, power, true);
  blrsMotorSet(ARM_RIGHT, power, true);
}

static void liftTask(void* ign){
  while (true){

    delay(20);
  }
}

void liftStartTask(){
  taskCreate(liftTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}
