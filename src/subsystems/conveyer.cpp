#include "main.h"

using namespace okapi;

Motor rollers(rollerPort, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

int rollerButtonCount;

void updateRollers()
{
  if (controller.getDigital(ControllerDigital::R1) == 1)
  {
    rollerButtonCount = 1;
  }
  else if(controller.getDigital(ControllerDigital::R2) == 1)
  {
    rollerButtonCount = 2;
  }
  else{
    rollerButtonCount = 3;
  }

  switch (rollerButtonCount)
  {
  case 1:
    rollers.moveVelocity(600);
    break;
  case 2:
    rollers.moveVelocity(-185);
    break;
  case 3:
    rollers.moveVelocity(0);
    break;
  }
}
