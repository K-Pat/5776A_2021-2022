#include "main.h"

int pneumaticButtonCount;

pros::ADIDigitalOut piston2 (clamp2);
pros::ADIDigitalOut piston (pneumaticPort);

void updatePneumatics()
{
   if (controller.getDigital(ControllerDigital::L2) == 1)
   {
     pneumaticButtonCount=1;
   }
   else if (controller.getDigital(ControllerDigital::L1) == 1)
   {
     pneumaticButtonCount=2;
   }
/*
   else if (controller.getDigital(ControllerDigital::A)==1){
     pneumaticButtonCount=3;
   }
   else if (controller.getDigital(ControllerDigital::Y)==1){
     pneumaticButtonCount=4;
   }
*/
   switch(pneumaticButtonCount)
   {
     case 1:
      piston.set_value(true);
      break;
     case 2:
      piston.set_value(false);
      break;
/*
     case 3:
      piston2.set_value(true);
      break;

     case 4:
      piston2.set_value(false);
      twoBarLift.moveVelocity(twoBarPID(-155));
      break;
      */
   }
}
