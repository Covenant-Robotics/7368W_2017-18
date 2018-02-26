#include "main.h"    // includes API.h and other headers

Encoder leftEncoder, rightEncoder;
int chassisLeftPos(){
  return encoderGet(leftEncoder);
}

int chassisRightPos(){
  return encoderGet(rightEncoder);
}

static fbc_t distanceController;
static fbc_pid_t distancePID;

static void _chassisPIDMove(int power) {
  blrsMotorSet(MOTOR_LEFT, power, false);
  blrsMotorSet(MOTOR_RIGHT, power, false);
//  printf("power %d\n", power);

}
void chassisReset (){
  encoderReset(leftEncoder);
  encoderReset(rightEncoder);
}
static void _chassisPIDReset () {
  encoderReset(leftEncoder);
  encoderReset(rightEncoder);
}

void chassisSet(int left, int right) {
blrsMotorSet(MOTOR_LEFT, left, false);
blrsMotorSet(MOTOR_RIGHT, right, false);
}

void chassisInit() {
  leftEncoder = encoderInit(ENCODER_LEFT_TOP, ENCODER_LEFT_BOTTOM, false);
  rightEncoder = encoderInit(ENCODER_RIGHT_TOP, ENCODER_RIGHT_BOTTOM, true);
  blrsMotorInit(MOTOR_LEFT, false, DRIVE_SLEW, NULL);
  blrsMotorInit(MOTOR_RIGHT, true, DRIVE_SLEW, NULL);
  fbcInit(&distanceController, _chassisPIDMove, chassisGetPos, _chassisPIDReset, NULL, -DRIVE_PID_DEADBAND, DRIVE_PID_DEADBAND, DRIVE_PID_TOLERANCE, DRIVE_PID_CONFIDENCE);
  fbcPIDInitializeData(&distancePID, DRIVE_KP, DRIVE_KI, DRIVE_KD, -DRIVE_INTEGRAL_CAP, DRIVE_INTEGRAL_CAP);
  fbcPIDInit(&distanceController, &distancePID);
}

void chassisPidAutotune() {
	fbcPIDAutotune(&distanceController, 5, 20, 5000, 1000, uart1, 0.01, 0.5, 0, 0.0001, 0, 0.001, 10, 5);
}

int chassisGetPos(){
  int leftPos, rightPos;
  leftPos = encoderGet(leftEncoder);
  rightPos = encoderGet(rightEncoder);
  return ((leftPos + rightPos) / 2);
}

void chassisPIDSet (int goal) {
  fbcSetGoal(&distanceController, goal);
  delay(10);
}
fbc_t* chassisGetPID () {
  return &distanceController;
}
int trueSpeed (int in) {
  printf("truespeed %d\n", in);
  return (in*in*in) / (127*127);

}
