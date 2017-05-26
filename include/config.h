#ifndef CONFIG_H
#define CONFIG_H

#include "main.h"

#define MOTOR_RIGHT_FRONT 2
#define MOTOR_RIGHT_BACK 3
#define MOTOR_LEFT_FRONT 4
#define MOTOR_LEFT_BACK 5
#define ARM_LEFT_TOP 6
#define ARM_LEFT_BOTTOM 7

#define ENCODER_LEFT_TOP 1
#define ENCODER_LEFT_BOTTOM 2
#define ENCODER_RIGHT_TOP 3
#define ENCODER_RIGHT_BOTTOM 4

#define DRIVE_SLEW 0.5f


//PID constants
#define DRIVE_PID 1
#define DRIVE_PID_DEADBAND 17
#define DRIVE_PID_TOLERANCE 30
#define DRIVE_PID_CONFIDENCE 5
#define DRIVE_KI 0.0F
#define DRIVE_KP 0.132F
#define DRIVE_KD 0.0015F
#define DRIVE_INTEGRAL_CAP 500



#endif
