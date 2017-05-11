
#ifndef _CHASSIS_H_
#define _CHASSIS_H_

// Sets the speeds of the left and right wheels of the chassis
void chassisSet(int left, int right);

void chassisInit();

int chassisGetPos();

int trueSpeed(int in);

#endif // _CHASSIS_H_
