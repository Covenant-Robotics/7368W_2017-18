
#ifndef _CHASSIS_H_
#define _CHASSIS_H_
#include "fbc.h"
// Sets the speeds of the left and right wheels of the chassis
void chassisSet(int left, int right);

void chassisInit();

int chassisLeftPos();

int chassisRightPos();

int chassisGetPos();

int trueSpeed(int in);

void chassisPIDSet (int goal);

fbc_t* chassisGetPID ();
void chassisReset();

/**
 * Example Autotune routine
 */
void chassisPidAutotune();

#endif // _CHASSIS_H_
