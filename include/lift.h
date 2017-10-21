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

void chainRun();
void chainSetPos(int goal);
void chainTaskSet();
void chainTaskInitialize();
void chainFindDeadband();
void chainPidAutotune();

TaskHandle coneResetTask();

void coneTaskSet();
void coneTaskInitialize();

int liftGetPos();
int liftGetSpeed();
int chainGetPos();

//New Functions
void stack(unsigned int height);
void chainSet(int power);
void liftSet(int power);
void clawSet(int power);
void mogoSet(int power);
void liftToDriverLoad();

#endif
