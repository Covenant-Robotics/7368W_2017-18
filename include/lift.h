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

int liftGetPos();
int liftGetSpeed();

#endif
