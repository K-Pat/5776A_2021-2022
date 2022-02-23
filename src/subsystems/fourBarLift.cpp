#include "main.h"

using namespace okapi;

Motor fourBarLift(fourBarLiftPort, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

double targetL;
double targetR;

int liftButtonCount;

typedef struct PID pid;

pid FB;

double fourBarPID(double setpoint)
{
  FB.kP = 0.5;
  FB.kI = 0.001;
  FB.kD = 0.001;

  FB.target = setpoint;
  FB.error = FB.target - fourBarLift.getPosition();
  FB.integral += FB.error;
  FB.derivative = FB.error - FB.prevError;
  FB.power = FB.kP * FB.error + FB.kI * FB.integral + FB.kD * FB.derivative;

  return FB.power;
}

void updateFourBarLiftMacro()
{

if (controller.getDigital(ControllerDigital::up) == 1)
{
  liftButtonCount = 1;
}

else if(controller.getDigital(ControllerDigital::down) == 1)
{
  liftButtonCount = 2;
}

else if (controller.getDigital(ControllerDigital::left) == 1)
{
  liftButtonCount = 3;
}
else if (controller.getDigital(ControllerDigital::right) == 1)
{
  liftButtonCount = 4;
}
switch (liftButtonCount)
{
case 1: //All the way up
  fourBarLift.moveVelocity(fourBarPID(-690));
  break;

case 3: //set height for driving with mogo
  fourBarLift.moveVelocity(fourBarPID(-550));
  break;

case 2: //all the way down
  fourBarLift.moveVelocity(fourBarPID(-15));
  break;
  case 4:
    fourBarLift.moveVelocity(0);
  break;

}

}
