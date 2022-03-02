#include "main.h"

using namespace okapi;

auto straight = IterativePosPIDController(0.001,0.0001,0.00015,0,TimeUtilFactory::withSettledUtilParams(0.3, 10000, 50_ms), std::make_unique<MedianFilter<5>>());

void rightAuton()
{
  //drive->moveDistance(8.8_ft);
  piston.set_value(false);//unclamp four bar
  piston2.set_value(true);//unclamp two bar
  translatePID(65, 1000);//move forward to the right neutral.
  pros::delay(10);
  piston.set_value(true);//clamp dow
  translatePID(-28, 1000);//move back
  //piston.set_value(false);//unclamp
  pros::delay(500);
  //translatePID(-8, 500);
  rotatePID(-95, 1000);
  piston2.set_value(true);
  translatePID(-28, 500);
  pros::delay(750);
  piston2.set_value(false);
  pros::delay(400);
  translatePID(25,750);
  fourBarLift.moveVelocity(fourBarPID(-690));
  rollers.moveVelocity(200);
  pros::delay(5000);
    /*
  straight.setTarget(1500);
  while (!straight.isSettled()) {
    double inputlb = leftBack.getPosition();
    double inputrb = rightBack.getPosition();
    double inputlf = leftFront.getPosition();
    double inputrf = rightFront.getPosition();

    double input = (inputlb+inputrb+inputlf+inputrf)/4;

    double newOutput = straight.step(input);

    leftBack.controllerSet(newOutput);
    rightBack.controllerSet(newOutput);
    leftFront.controllerSet(newOutput);
    rightFront.controllerSet(newOutput);

    pros::delay(10); // Run the control loop at 10ms intervals
  }
  */
  pros::delay(10);






}

void progSkills(){
  piston.set_value(false);//unclamp four bar
  piston2.set_value(true);//unclamp two bar
  translatePID(56, 1000);//move forward to the right neutral.
  piston.set_value(true);//clamp down
  pros::delay(1000);
  rotatePID(90,1000);
  pros::delay(500);

  translatePID(56,1000);

}

void leftAuton()
{
  piston.set_value(false);
  piston2.set_value(true);
  translatePID(50, 1000);//fprward
  piston.set_value(true);//clamp down
  //fourBarLift.moveVelocity(100);
  //fourBarLift2.moveVelocity(100);//lift rise
  pros::delay(1000);
  translatePID(-65,3000);//goes back
  rotatePID(-95, 1000);//turn to face the alliance mogo
  pros::delay(500);
  translatePID(-10, 500);//move  forward to the mogo
  pros::delay(125);
  piston2.set_value(false);//clamp
  fourBarLift.moveVelocity(100);
  pros::delay(500);
  rollers.moveVelocity(200);//rings.
  pros::delay(5000);
}
