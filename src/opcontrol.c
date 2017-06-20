#include "main.h"

static int clamp(int in) { return (abs(in) > 15) ? in : 0; }

void operatorControl() {
  bool track_lift = true;
  while (1) {
    int power = clamp(joystickGetAnalog(1, 3));
    int turn = clamp(joystickGetAnalog(1, 1));

    chassisSet(power + turn, power - turn);

    // if (buttonGetState(JOY1_6U)) {
    //   liftOpSet(127);
    //   track_lift = true;
    // }
    // else if (buttonGetState(JOY1_6D)) {
    //   liftOpSet(-127);
    //   track_lift = true;
    // }
    // else if (liftGetSpeed() != 0 && track_lift) {
    //   liftOpSet(0);
    //   track_lift = true;
    // }
    // else if (liftGetSpeed() == 0 && track_lift) { //just started pid
    //   track_lift = false;
    //   liftSetPos(liftGetPos());
    //   liftPID();
    // }
    // else {
    //   track_lift = false;
    //   liftPID();
    // }

    if (buttonGetState(JOY1_6U))
      liftOpSet(127);
    else if (buttonGetState(JOY1_6D))
      liftOpSet(-127);
    else
      liftOpSet(0);

    delay(20);
  }
}
