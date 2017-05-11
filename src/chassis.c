#include "main.h"    // includes API.h and other headers

Encoder leftEncoder, rightEncoder;

void chassisSet(int left, int right) {
blrsMotorSet(MOTOR_LEFT_BACK, left, false);
blrsMotorSet(MOTOR_LEFT_FRONT, left, false);
blrsMotorSet(MOTOR_RIGHT_BACK, right, false);
blrsMotorSet(MOTOR_RIGHT_FRONT, right, false);
}

void chassisInit() {
  leftEncoder = encoderInit(ENCODER_LEFT_TOP, ENCODER_LEFT_BOTTOM, false);
  rightEncoder = encoderInit(ENCODER_RIGHT_TOP, ENCODER_RIGHT_BOTTOM, false);
  blrsMotorInit(MOTOR_LEFT_FRONT, false, DRIVE_SLEW, trueSpeed);
  blrsMotorInit(MOTOR_LEFT_BACK, false, DRIVE_SLEW, trueSpeed);
  blrsMotorInit(MOTOR_RIGHT_FRONT, true, DRIVE_SLEW, trueSpeed);
  blrsMotorInit(MOTOR_RIGHT_BACK, true, DRIVE_SLEW, trueSpeed);


}

int chassisGetPos(){
  int leftPos, rightPos;
  leftPos = encoderGet(leftEncoder);
  rightPos = encoderGet(rightEncoder);
  return ((leftPos + rightPos) / 2);
}

int trueSpeed (int in) {
  return (in*in*in) / (127*127);
}
