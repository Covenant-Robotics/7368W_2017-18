#include "main.h"
int joystickGetAnalog ( unsigned char joystick,   // the joystick slot to check (1 for master, 2 for partner)
                        unsigned char axis        // One of the joystick channels on a VEX Joystick: 1, 2, 3, 4, ACCEL_X, or ACCEL_Y
                      );

void motorSet ( unsigned char channel,  // motor channel to set from 1-10
                int speed               // new signed speed. -127 is full reverse, 127 full forward, 0 off
              );
void operatorControl() {
  int power;
  int turn;
    while (1) {
        power = joystickGetAnalog(1, 3); // vertical axis on left joystick
        turn  = joystickGetAnalog(1, 1); // horizontal axis on left joystick
        chassisSet(power + turn, power - turn);
        delay(20);
if (buttonIsNewPress(JOY1_8U)) {
  autonomous();
} 
    }
}
