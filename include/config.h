#ifndef CONFIG_H
#define CONFIG_H

#include "main.h"

#define MOTOR_RIGHT_FRONT 8
#define MOTOR_RIGHT_BACK 9
#define MOTOR_LEFT_FRONT 2
#define MOTOR_LEFT_BACK 3
#define ARM_LEFT 5
#define ARM_RIGHT 6
#define CLAW 7
#define INTAKE 1
#define CHAIN 4

#define ENCODER_LEFT_TOP 1
#define ENCODER_LEFT_BOTTOM 2
#define ENCODER_RIGHT_TOP 3
#define ENCODER_RIGHT_BOTTOM 4
#define ARM_POT 1
#define CHAIN_POT 2
#define MOGO_POT 3
#define DRIVE_SLEW 0.5f


//Drive constants
#define DRIVE_PID 1
#define DRIVE_PID_DEADBAND 17
#define DRIVE_PID_TOLERANCE 30
#define DRIVE_PID_CONFIDENCE 5
#define DRIVE_KI 0.0F
#define DRIVE_KP 0.132F
#define DRIVE_KD 0.0015F
#define DRIVE_INTEGRAL_CAP 500

//Lift Constants
#define LIFT_POS_DEADBAND 22
#define LIFT_NEG_DEADBAND -5
#define LIFT_PID_TOL 30
#define LIFT_PID_CONF 5
#define LIFT_KP 0.2f
#define LIFT_KD 0.001f

#define LIFT_BOTTOM 1950
#define LIFT_TOP 3600
#define LIFT_TIP_CONE 2200

#define LIFT_SLEW 0.35f
//Chain Constants
#define CHAIN_POS_DEADBAND 27
#define CHAIN_NEG_DEADBAND -9
#define CHAIN_PID_TOL 30
#define CHAIN_PID_CONF 5
#define CHAIN_KP 0.4f
#define CHAIN_KD 0.01f


#endif
