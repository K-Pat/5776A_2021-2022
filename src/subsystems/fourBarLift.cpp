#include "main.h"

using namespace okapi;

Motor fourBarLift(fourBarLiftPort, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
//Motor fourBarLift2(fourBarLiftPort2, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

Potentiometer pot = Potentiometer(pot1);

double targetL;
double targetR;

int liftButtonCount;

typedef struct PID pid;

pid TWOB;
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


void autonFourBarPID(double setpoint)
{
  while (true)
  {
    FB.kP = 0.85;
    FB.kI = 0;
    FB.kD = 0.05;

    FB.target = setpoint;
    FB.error = FB.target - fourBarLift.getPosition();
    FB.integral += FB.error;
    FB.derivative = FB.error - FB.prevError;
    FB.power = FB.kP * FB.error + FB.kI * FB.integral + FB.kD * FB.derivative;

    fourBarLift.moveVelocity(FB.power);
    fourBarLift2.moveVelocity(FB.power);

    if (abs(FB.error) < 7)
    {
      fourBarLift.setBrakeMode(AbstractMotor::brakeMode::hold);
      //fourBarLift2.setBrakeMode(AbstractMotor::brakeMode::hold);

      break;
    }

    pros::delay(10);
  }
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
//get some bitches

else if (controller.getDigital(ControllerDigital::left) == 1)
{
  liftButtonCount = 3;
}
else if (controller.getDigital(ControllerDigital::right) == 1)
{
  liftButtonCount = 4;
}
/*
else if(abs(controller.getAnalog(ControllerAnalog::rightY))>0){
  liftButtonCount = 3;
}*/

switch (liftButtonCount)
{
case 1: //All the way up
  fourBarLift.moveVelocity(fourBarPID(690));
  //fourBarLift2.moveVelocity(fourBarPID(690));
  break;

case 3: //set height for driving with mogo
  fourBarLift.moveVelocity(fourBarPID(550));
  //fourBarLift2.moveVelocity(fourBarPID(550));
  break;

case 2: //all the way down
  fourBarLift.moveVelocity(fourBarPID(15));
  //fourBarLift2.moveVelocity(fourBarPID(15));
  break;
  /*
case 4: //platform scoring
  fourBarLift.moveVelocity(fourBarPID(250));
  fourBarLift2.moveVelocity(fourBarPID(250));
  break;
  */
  /*
case 3:
  double target = 7*controller.getAnalog(ControllerAnalog::rightY);
  //auto pid = IterativeControllerFactory::posPID(0.5, 0.001, 0.001);
  fourBarLift.moveVelocity(fourBarPID(target));
  fourBarLift2.moveVelocity(fourBarPID(target));

  while (!pid.isSettled()) {
  double pidValue = pid.step(fourBarLift.getPosition());
  fourBarLift.controllerSet(pidValue);
  fourBarLift2.controllerSet(pidValue);

  break;
  */
  case 4:
    fourBarLift.moveVelocity(0);
    //fourBarLift2.moveVelocity(0);
  break;

}


  //Joystick values have a range of -100 to 100, so you multiply by a constant "7" to change the full range to -700 to 700 which is more important useful 97
}
