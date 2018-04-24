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
  if(analogRead(AUTON_POT) < 500 && analogRead(AUTON_POT) >= 0){ //auton Left
    lcdSetText(uart1, 1, "auton Left");
    chassisReset();
    // while(analogRead(CHAIN_POT) < 1500){      //out then in on chainbar to undo starting rubber bands
    //   chainSet(127);
    //   delay(20);
    // }
    // while(analogRead(CHAIN_POT) > 200){
    //   chainSet(-127);
    //   delay(20);
    // }
    // chainSet(0);
    while(analogRead(ARM_POT) > 1550){         //arm height to clear mogo intake
      liftSet(127);
  //    chassisSet(80,80);
      delay(20);
    }
    liftSet(0);
    while(analogRead(MOGO_POT) > 650){          // out of mogo intake
      blrsMotorSet(INTAKE, 127, true);
      blrsMotorSet(INTAKE2, 127, true);
      chassisSet(60,60);
      delay(20);
    }
    blrsMotorSet(INTAKE, 0, true);
    blrsMotorSet(INTAKE2, 0, true);
    while(chassisGetPos() < 1200){              //drive into mogo
      chassisSet(80, 80);
      delay(20);
    }
    chassisSet(0, 0);
    chassisReset();
    delay(200);
    while(analogRead(MOGO_POT) < 2700){         //intake mogo
      blrsMotorSet(INTAKE, -127, true);
      blrsMotorSet(INTAKE2, -127, true);
      delay(20);
    }
    blrsMotorSet(INTAKE, 0, true);
    blrsMotorSet(INTAKE2, 0, true);
    while(analogRead(ARM_POT) < 1400){          //drop the arm back down
      liftSet(-127);
      chassisSet(-127,-127);
      delay(20);
    }
    liftSet(0);
    blrsMotorSet(CLAW, -100, true);             //stack the preload cone
    delay(300);
    blrsMotorSet(CLAW, 0, true);
    while(chassisGetPos() > -500){             //return to scoring zone
      chassisSet(-127, -127);
      delay(20);
    }
    while(chassisGetPos() > -1500){             //return to scoring zone
      chassisSet(-80, -40);
      delay(20);
    }
    chassisSet(0, 0);
    delay(750);
    chassisReset();
    while(chassisLeftPos() > -140 || chassisRightPos() < 140){
      chassisSet(-80, 80);
      delay(20);
    }
    chassisSet(100, -100);
    delay(200);
    chassisReset();
    chassisSet(40, 40);
    delay(200);
    while(chassisGetPos() < 500){
      chassisSet(127, 127);
      delay(20);
    }
    chassisSet(0,0);
    chassisReset();
    blrsMotorSet(CLAW, -100, true);
    while(analogRead(ARM_POT) > 1300){         //arm height to clear mogo intake
      liftSet(80);
      delay(20);
    }
    liftSet(0);
    blrsMotorSet(CLAW, 0, true);
    while(analogRead(MOGO_POT) > 1300){          // out of mogo intake
      blrsMotorSet(INTAKE, 127, true);
      blrsMotorSet(INTAKE2, 127, true);
      chassisSet(50,50);
      delay(20);
    }
    chassisSet(0,0);
    blrsMotorSet(INTAKE, 0, true);
    blrsMotorSet(INTAKE2, 0, true);
    chassisSet(-80,-80);
    delay(500);
    chassisSet(100,100);
    blrsMotorSet(INTAKE, -40, true);
    blrsMotorSet(INTAKE2, -40, true);
    delay(300);
    chassisSet(-100,-100);
    blrsMotorSet(INTAKE, 80, true);
    blrsMotorSet(INTAKE2, 80, true);
    delay(300);
    while(analogRead(MOGO_POT) < 2700){         //return mogo intake
      blrsMotorSet(INTAKE, -80, true);
      blrsMotorSet(INTAKE2, -80, true);
      chassisSet(20, 20);
      delay(20);
    }
    blrsMotorSet(INTAKE, 0, true);
    blrsMotorSet(INTAKE2, 0, true);
    chassisReset();
    while(chassisGetPos() > -300){
      chassisSet(-127, -127);
      delay(20);
    }
    chassisSet(0,0);
  } //end of autonLeft
////////////////////////////////////////////////////////////////////////////////
else if(analogRead(AUTON_POT) > 500 && analogRead(AUTON_POT) < 1400){ //auton left 5-point
  while(analogRead(ARM_POT) > 1550){         //arm height to clear mogo intake
    liftSet(127);
//    chassisSet(80,80);
    delay(20);
  }
  liftSet(0);
  while(analogRead(MOGO_POT) > 650){          // out of mogo intake
    blrsMotorSet(INTAKE, 127, true);
    blrsMotorSet(INTAKE2, 127, true);
    chassisSet(60,60);
    delay(20);
  }
  blrsMotorSet(INTAKE, 0, true);
  blrsMotorSet(INTAKE2, 0, true);
  while(chassisGetPos() < 1200){              //drive into mogo
    chassisSet(80, 80);
    delay(20);
  }
  chassisSet(0, 0);
  chassisReset();
  delay(200);
  while(analogRead(MOGO_POT) < 2700){         //intake mogo
    blrsMotorSet(INTAKE, -127, true);
    blrsMotorSet(INTAKE2, -127, true);
    delay(20);
  }
  blrsMotorSet(INTAKE, 0, true);
  blrsMotorSet(INTAKE2, 0, true);
  while(analogRead(ARM_POT) < 1400){          //drop the arm back down
    liftSet(-127);
  //  chassisSet(-127,-127);
    delay(20);
  }
  liftSet(0);
  blrsMotorSet(CLAW, -100, true);             //stack the preload cone
  delay(300);
  blrsMotorSet(CLAW, 0, true);
while(analogRead(BAR_POT) > 3680){            //grab second cone
  blrsMotorSet(CHAIN, 100, true);
  blrsMotorSet(CLAW, -100, true);
}
blrsMotorSet(CHAIN, 0, true);
blrsMotorSet(CLAW, -100, true);
delay(300);
while(analogRead(ARM_POT) > 1550){
  liftSet(100);
  blrsMotorSet(CHAIN, -100, true);
  blrsMotorSet(CLAW, 0, true);
}
}
////////////////////////////////////////////////////////////////////////////////
  else if(analogRead(AUTON_POT) >= 1400 && analogRead(AUTON_POT) <= 2300){ //auton Middle
    lcdSetText(uart1, 1, "auton mid");
    chassisReset();
    // while(analogRead(CHAIN_POT) < 2600){
    //   chainSet(80);
    //   delay(20);
    // }
    // chainSet(0);
    // delay(20);
    chainSet(100);
    delay(1000);
    chainSet(0);
    while(analogRead(ARM_POT) > 700){
      liftSet(80);
      delay(20);
    }
    liftSet(0);
    delay(20);
    while(chassisRightPos() < 375){
      chassisSet(25, 25);
      delay(20);
    }
    chassisSet(0, 0);
    chassisReset();
    delay(500);
    while(analogRead(ARM_POT) < 800){
      liftSet(-40);
      delay(20);
    }
    liftSet(0);
    delay(500);
    blrsMotorSet(CLAW, -100, true);
    while(analogRead(ARM_POT) > 700){
      liftSet(80);
      delay(20);
    }
    liftSet(0);
    blrsMotorSet(CLAW, 0, true);
    chassisReset();
    while(chassisLeftPos() > -375){
      chassisSet(-100, -100);
    }
    chassisSet(0, 0);
  } //end of auton Mid
////////////////////////////////////////////////////////////////////////////////
else if(analogRead(AUTON_POT) > 2300 && analogRead(AUTON_POT) < 3700){ //auton right 5 point

}
////////////////////////////////////////////////////////////////////////////////
  else if(analogRead(AUTON_POT) > 3700 && analogRead(AUTON_POT) <= 4095){ //auton right

    lcdSetText(uart1, 1, "auton right");
    // while(analogRead(CHAIN_POT) < 1500){      //out then in on chainbar to undo starting rubber bands
    //   chainSet(127);
    //   delay(20);
    // }
    // while(analogRead(CHAIN_POT) > 200){
    //   chainSet(-127);
    //   delay(20);
    // }
    // chainSet(0);
    while(analogRead(ARM_POT) > 1550){         //arm height to clear mogo intake
      liftSet(127);
//      chassisSet(80, 80);
      delay(20);
    }
    liftSet(0);
    while(analogRead(MOGO_POT) > 650){          // out of mogo intake
      blrsMotorSet(INTAKE, 127, true);
      blrsMotorSet(INTAKE2, 127, true);
      chassisSet(60, 60);
      delay(20);
    }
    blrsMotorSet(INTAKE, 0, true);
    blrsMotorSet(INTAKE2, 0, true);
    while(chassisGetPos() < 1200){              //drive into mogo
      chassisSet(80, 80);
      delay(20);
    }
    chassisSet(0, 0);
    chassisReset();
    delay(200);
    while(analogRead(MOGO_POT) < 2700){         //intake mogo
      blrsMotorSet(INTAKE, -127, true);
      blrsMotorSet(INTAKE2, -127, true);
      delay(20);
    }
    blrsMotorSet(INTAKE, 0, true);
    blrsMotorSet(INTAKE2, 0, true);
    while(analogRead(ARM_POT) < 1400){          //drop the arm back down
      liftSet(-127);
      chassisSet(-127,-127);
      delay(20);
    }
    liftSet(0);
    blrsMotorSet(CLAW, -100, true);             //stack the preload cone
    delay(300);
    blrsMotorSet(CLAW, 0, true);
    while(chassisGetPos() > -500){             //return to scoring zone
      chassisSet(-127, -127);
      delay(20);
    }
    while(chassisGetPos() > -1600){             //return to scoring zone
      chassisSet(-30, -80);
      delay(20);
    }
    chassisSet(0, 0);
    delay(750);
    chassisReset();
    while(chassisLeftPos() < 140  || chassisRightPos() > -140){
      chassisSet(80, -80);
      delay(20);
    }
    chassisSet(-100, 100);
    delay(20);
    chassisReset();
    chassisSet(40,40);
    delay(200);
    while(chassisGetPos() < 500){
      chassisSet(127, 127);
      delay(20);
    }
    chassisSet(0,0);
    chassisReset();
    blrsMotorSet(CLAW, -100, true);
    while(analogRead(ARM_POT) > 1300){         //arm height to clear mogo intake
      liftSet(80);
      delay(20);
    }
    liftSet(0);
    blrsMotorSet(CLAW, 0, true);
    while(analogRead(MOGO_POT) > 1300){          // out of mogo intake
      blrsMotorSet(INTAKE, 127, true);
      blrsMotorSet(INTAKE2, 127, true);
      chassisSet(50,50);
      delay(20);
    }
    chassisSet(0,0);
    blrsMotorSet(INTAKE, 0, true);
    blrsMotorSet(INTAKE2, 0, true);
    chassisSet(-80,-80);
    delay(500);
    chassisSet(100,100);
    blrsMotorSet(INTAKE, -40, true);
    blrsMotorSet(INTAKE2, -40, true);
    delay(300);
    chassisSet(-100,-100);
    blrsMotorSet(INTAKE, 80, true);
    blrsMotorSet(INTAKE2, 80, true);
    delay(300);
    while(analogRead(MOGO_POT) < 2700){         //return mogo intake
      blrsMotorSet(INTAKE, -80, true);
      blrsMotorSet(INTAKE2, -80, true);
      chassisSet(20, 20);
      delay(20);
    }
    blrsMotorSet(INTAKE, 0, true);
    blrsMotorSet(INTAKE2, 0, true);
    chassisReset();
    while(chassisGetPos() > -300){
      chassisSet(-127, -127);
      delay(20);
    }
    chassisSet(0,0);
} //end of auton Right
////////////////////////////////////////////////////////////////////////////////
} //end of autonomous
