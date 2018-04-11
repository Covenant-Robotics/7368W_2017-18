#ifndef CONFIG_H
#define CONFIG_H

#include "main.h"

#define ARM_LEFT 5 //on power expander
#define ARM_RIGHT 6 //on power expander
#define CLAW 3 //on power expander
#define INTAKE 1
#define INTAKE2 2
#define CHAIN 8
#define MOTOR_LEFT 4
#define MOTOR_RIGHT 7

#define ENCODER_LEFT_TOP 1
#define ENCODER_LEFT_BOTTOM 2
#define ENCODER_RIGHT_TOP 3
#define ENCODER_RIGHT_BOTTOM 4

#define ARM_POT 1
#define BAR_POT 7 //out=3680, in=1400
#define CLAW_POT 5 //closed=3685, open=3470
#define MOGO_POT 3
#define AUTON_POT 4
#define CHAIN_POT 2 //unused

#define DRIVE_SLEW 0.5f
#define ARM_SLEW 0.5f


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
#define CHAIN_POS_DEADBAND 10
#define CHAIN_NEG_DEADBAND -10
#define CHAIN_PID_TOL 30
#define CHAIN_PID_CONF 5
#define CHAIN_KP 0.1f
#define CHAIN_KD 0.01f


#define CHAIN_POS_DB_STACK 50
#define CHAIN_NEG_DB_STACK -10
#define CHAIN_POS_DB_INTAKE 10
#define CHAIN_NEG_DB_INTAKE -50


#define CHAIN_INTAKE 2700
#define CHAIN_STACK 500

#define LIFT_DRIVER_POS 1400 //needs testing to find this

//mogo PID Constants
#define MOGO_POS_DEADBAND 20
#define MOGO_NEG_DEADBAND -20
#define MOGO_PID_TOL 10
#define MOGO_PID_CONF 5
#define MOGO_KP 0.1f


#endif
