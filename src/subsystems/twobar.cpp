#include "main.h"

using namespace okapi;

int twoBarButtonCount;

double targetTwoBar;

pros::ADIDigitalOut piston3(clamp3);

typedef struct PID pid;

pid TB;

void updateTwoBarLiftMacro()
{
  if (controller.getDigital(ControllerDigital::X) == 1)
  {
    twoBarButtonCount = 1;
  }
  else if(controller.getDigital(ControllerDigital::B) == 1)
  {
    twoBarButtonCount = 2;

  }
  switch (twoBarButtonCount)
  {
  case 1:
    piston2.set_value(true);
    piston3.set_value(true);
    break;
  case 2:
    piston2.set_value(false);
    piston3.set_value(false);
    //twoBarLift.moveVelocity(twoBarPID(-165));//160 is original
    break;
  }
}
