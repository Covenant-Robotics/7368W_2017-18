/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

void autonomous() {
////////////////////////////////////////////////////////////////////////////////
  if(analogRead(AUTON_POT) < 1250 && analogRead(AUTON_POT) >= 0){
    lcdSetText(uart1, 1, "autonLeft");
  }

////////////////////////////////////////////////////////////////////////////////
  else if(analogRead(AUTON_POT) >= 1250 && analogRead(AUTON_POT) <= 3000){
    lcdSetText(uart1, 1, "auton mid");
    chassisReset();
    while(analogRead(CHAIN_POT) < 2600){
      chainSet(80);
    }
    chainSet(0);
    delay(20);
    while(analogRead(ARM_POT) > 700){
      liftSet(80);
    }
    liftSet(0);
    delay(20);
    while(chassisRightPos() < 325){
      chassisSet(25, 25);
    }
    chassisSet(0, 0);
    chassisReset();
    delay(500);
    while(analogRead(ARM_POT) < 800){
      liftSet(-40);
    }
    liftSet(0);
    delay(500);
    blrsMotorSet(CLAW, -100, true);
    while(analogRead(ARM_POT) > 700){
      liftSet(80);
    }
    liftSet(0);
    blrsMotorSet(CLAW, 0, true);
  }
////////////////////////////////////////////////////////////////////////////////
  else if(analogRead(AUTON_POT) > 3000 && analogRead(AUTON_POT) <= 4095){
    lcdSetText(uart1, 1, "auton right");
    while(analogRead(CHAIN_POT) < 2000){      //out then in on chainbar to undo starting rubber bands
      chainSet(80);
    }
    while(analogRead(CHAIN_POT) > 200){
      chainSet(-80);
    }
    chainSet(0);
    while(analogRead(ARM_POT) > 1300){         //arm height to clear mogo intake
      liftSet(80);
    }
    liftSet(0);
    while(analogRead(MOGO_POT) > 800){          // out of mogo intake
      blrsMotorSet(INTAKE, 127, true);
    }
    blrsMotorSet(INTAKE, 0, true);
    while(chassisGetPos() < 1500){              //drive into mogo
      chassisSet(127, 127);
    }
    chassisSet(0, 0);
    chassisReset();
    while(analogRead(MOGO_POT) < 2500){         //intake mogo
      blrsMotorSet(INTAKE, -80, true);
    }
    blrsMotorSet(INTAKE, 0, true);
    while(chassisGetPos() > -1300){             //return to scoring zone
      chassisSet(-127, -127);
    }
    chassisSet(0, 0);
    chassisReset();
    while(analogRead(ARM_POT) < 1400){          //drop the arm back down
      liftSet(-60);
    }
    liftSet(0);
    blrsMotorSet(CLAW, -100, true);             //stack the preload cone
    delay(200);
    blrsMotorSet(CLAW, 0, true);
  chassisReset();
  while(chassisLeftPos() < 400);{
    chassisSet(50, -50);
}
chassisSet(0, 0);
}
////////////////////////////////////////////////////////////////////////////////
}
