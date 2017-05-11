
#ifndef _CHASSIS_H_
#define _CHASSIS_H_
#include "fbc.h"
// Sets the speeds of the left and right wheels of the chassis
void chassisSet(int left, int right);

void chassisInit();

int chassisGetPos();

int trueSpeed(int in);

void chassisPIDSet (int goal);

fbc_t* chassisGetPID ();

#endif // _CHASSIS_H_
