/**
 * @file Lift Module
 */
#ifndef _LIFT_H_
#define _LIFT_H_

#include "main.h"

#define LIFT_INCREMENT_DELTA 20

void liftInit();

void liftStartTask();
void liftEndTask();

void liftOpSet(int power);
void liftPIDHold();
void liftIncrementPos();
void liftDecrementPos();
void liftSnapToPos();
void liftPID();
void liftSetPos(int pos);
void liftSet(int power);

void chainRun();
void chainSetPos(int goal);
void chainTaskSet();
void chainTaskInitialize();
void chainFindDeadband();
void chainPidAutotune();
void chainSet(int power);
void mogoSetPos(int goal);

void mogoOut(void *param);
void mogoIn(void *param);
void mogoTasksInit();
void mogoInResume();
void mogoOutResume();
void mogoInSuspend();
void mogoOutSuspend();


TaskHandle coneResetTask();

void coneTaskSet();
void coneTaskInitialize();

int liftGetPos();
int liftGetSpeed();
int chainGetPos();


void liftAutoReturnTaskInit();
void liftAutoReturnSuspend();
void liftAutoReturnResume();

#endif
