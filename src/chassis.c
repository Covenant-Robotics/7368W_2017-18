#include "main.h"    // includes API.h and other headers

Encoder leftEncoder, rightEncoder;

static fbc_t distanceController;
static fbc_pid_t distancePID;

static void _chassisPIDMove(int power) {
  blrsMotorSet(MOTOR_LEFT_BACK, power, false);
  blrsMotorSet(MOTOR_LEFT_FRONT, power, false);
  blrsMotorSet(MOTOR_RIGHT_BACK, power, false);
  blrsMotorSet(MOTOR_RIGHT_FRONT, power, false);
//  printf("power %d\n", power);

}

static void _chassisPIDReset () {
  encoderReset(leftEncoder);
  encoderReset(rightEncoder);
}

void chassisSet(int left, int right) {
blrsMotorSet(MOTOR_LEFT_BACK, left, false);
blrsMotorSet(MOTOR_LEFT_FRONT, left, false);
blrsMotorSet(MOTOR_RIGHT_BACK, right, false);
blrsMotorSet(MOTOR_RIGHT_FRONT, right, false);

}

void chassisInit() {
  leftEncoder = encoderInit(ENCODER_LEFT_TOP, ENCODER_LEFT_BOTTOM, false);
  rightEncoder = encoderInit(ENCODER_RIGHT_TOP, ENCODER_RIGHT_BOTTOM, true);
  blrsMotorInit(MOTOR_LEFT_FRONT, false, DRIVE_SLEW, NULL);
  blrsMotorInit(MOTOR_LEFT_BACK, false, DRIVE_SLEW, NULL);
  blrsMotorInit(MOTOR_RIGHT_FRONT, true, DRIVE_SLEW, NULL);
  blrsMotorInit(MOTOR_RIGHT_BACK, true, DRIVE_SLEW, NULL);
  blrsMotorInit(ARM_LEFT, false, NULL, NULL);
  blrsMotorInit(ARM_RIGHT, true, NULL, NULL);
  fbcInit(&distanceController, _chassisPIDMove, chassisGetPos, _chassisPIDReset, -DRIVE_PID_DEADBAND, DRIVE_PID_DEADBAND, DRIVE_PID_TOLERANCE, DRIVE_PID_CONFIDENCE);
  fbcPIDInitializeData(&distancePID, DRIVE_KP, DRIVE_KI, DRIVE_KD, -DRIVE_INTEGRAL_CAP, DRIVE_INTEGRAL_CAP);
  fbcPIDInit(&distanceController, &distancePID);
}


int chassisGetPos(){
  int leftPos, rightPos;
  int average;
  leftPos = encoderGet(leftEncoder);
  rightPos = encoderGet(rightEncoder);
  average = (leftPos + rightPos) / 2;
  printf("encoderValue %d\n", average);
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
